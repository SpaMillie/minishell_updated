/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:06:44 by tparratt          #+#    #+#             */
/*   Updated: 2024/07/18 12:45:11 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parent(t_mini *line, t_tokens *token, t_fds *cur)
{
	if (line->i < line->pipe_num)
	{
		if (line->i != 0)
		{
			if (cur->in != -2 && close(cur->in) == -1)
				cleanup_close(line, token);
			cur->in = -2;
			if (has_input(&token[line->i]))
				line->input_fd = -2;
		}
		if (cur->out != -2 && close(cur->out) == -1)
			cleanup_close(line, token);
		cur->out = -2;
		if (has_output(&token[line->i]))
			line->output_fd = -2;
	}
	close_cleanup(line);
}

static void	child(t_tokens *token, t_mini *line, t_fds *cur)
{
	if (!ft_strncmp(token[line->i].command[0], "./minishell", 12))
		shell_lvl_check(line, token);
	redirections(line, token, cur);
	if (is_builtin(token[line->i].command[0]))
	{
		execute_builtin(&token[line->i], line);
		exit(line->err_num);
	}
	else
	{
		close_cleanup(line);
		if (execve(line->paths[line->i], token[line->i].command,
				line->envp) == -1)
		{
			ft_putstr_fd("minishell: execve failed", 2);
			cleanup(line, token, 1);
			exit(1);
		}
	}
}

static int	set_error(t_tokens *token, t_mini *line, int check)
{
	if (check == -1 || token[line->i].command[0] == NULL
		|| token[line->i].command[0][0] == 9)
	{
		if (check == -1)
			line->err_num = 1;
		line->flag = 1;
		line->i++;
		return (1);
	}
	return (0);
}

static void	fork_and_execute(t_tokens *token, t_mini *line, t_fds cur)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		print_error("minishell: failed to fork");
		cleanup(line, token, 1);
		exit(1);
	}
	if (pid == 0)
		child(token, line, &cur);
	else
		parent(line, token, &cur);
}

static t_fds	set_path_fds(int check, t_tokens *token, t_mini *line, int prev)
{	
	t_fds	current;

	if (check != -1 && token[line->i].command[0] != NULL
		&& !(is_builtin(token[line->i].command[0])))
	{
		if (get_path(token[line->i].command, line, token) == -1)
			malloc_failure(line, token);
	}
	else
		unnecessary_path(line, token);
	current = set_fds(line, &token[line->i], &prev);
	return (current);
}

void	execute(t_tokens *token, t_mini *line)
{
	int		check;
	t_fds	cur;
	int		prev;

	line->i = 0;
	prev = -2;
	if (line->pipe_num == 1 && token[line->i].command[0] != NULL
		&& is_builtin(token[line->i].command[0]))
	{
		single_builtin(token, line);
		return ;
	}
	while (line->i < line->pipe_num)
	{
		line->flag = 0;
		line->err_num = 0;
		check = opening(&token[line->i], line);
		cur = set_path_fds(check, token, line, prev);
		prev = cur.close;
		if (set_error(token, line, check))
			continue ;
		fork_and_execute(token, line, cur);
		line->i++;
	}
	wait_for_child(line, token);
}
