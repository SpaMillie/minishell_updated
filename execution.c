/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:06:44 by tparratt          #+#    #+#             */
/*   Updated: 2024/07/09 18:22:34 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parent(t_mini *line, t_tokens *token, t_fds *cur)
{
	if (line->i < line->pipe_num)
	{
		if (cur->out != -2 && close(cur->out) == -1)
			cleanup_close(line, token);
	}
	line->input_fd = -2;
	line->output_fd = -2;	
}

static void	child(t_tokens *token, t_mini *line, t_fds *cur)
{
	if (!ft_strncmp(token[line->i].command[0], "./minishell", 12)) //what if token[line->i].command[0] == ./minishellsoemthing?
		shell_lvl_check(line, token);
	redirections(line, token, cur);
	if (is_builtin(token[line->i].command[0]))
	{
		execute_builtin(&token[line->i], line);
		exit(line->err_num);
	}
	else
	{
		if (execve(line->paths[line->i], token[line->i].command, line->envp) == -1)
		{
			ft_putstr_fd("minishell: execve failed", 2);
			cleanup(line, token, 1);
			exit(1);
		}
	}
}

static void	set_error(t_tokens *token, t_mini *line, int check)
{
	if (check == -1)
		line->err_num = 1;
	else if (token[line->i].command[0][0] == 9)
		line->err_num = 127;
	line->i++;
}

void	set_path(int check, t_tokens *token, t_mini *line)
{	
	if (check != -1 && !(is_builtin(token[line->i].command[0])))
	{
		if (get_path(token[line->i].command, line, token) == -1)
			malloc_failure(line, token);
	}
	else
		unnecessary_path(line, token);	
}

void	execute(t_tokens *token, t_mini *line)
{
	pid_t	pid;
	int		check;
	t_fds	cur;
	int		prev;

	line->i = 0;
	prev = -2;
	if (line->pipe_num == 1 && is_builtin(token[line->i].command[0]))
		return (single_builtin(token, line));
	while (line->i < line->pipe_num)
	{
		line->flag = 0;
		line->err_num = 0;
		check = opening(&token[line->i], line);
		set_path(check, token, line);
		cur = set_fds(line, &token[line->i], &prev);
		prev = cur.close;
		if (check == -1 || token[line->i].command[0][0] == 9)
		{
			set_error(token, line, check);
			continue ;
		}
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
			child(token, line, &cur);
		else
			parent(line, token, &cur);
		line->i++;
	}
	wait_for_child(line);
}
