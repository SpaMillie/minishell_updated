/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:59:50 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/18 15:56:59 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_builtin(t_tokens *token, t_mini *line)
{		
	int		fd[2];
	t_fds	cur;

	if (init_fd(&fd[0], &fd[1]) == -1)
	{
		cleanup(line, token, 1);
		exit (1);
	}
	opening(&token[line->i], line);
	unnecessary_path(line, token);
	cur = set_fds(line, &token[line->i], &fd[0]);
	redirections(line, &token[line->i], &cur);
	if (line->input_fd != -1 && line->output_fd != -1)
	{
		line->err_num = 0;
		execute_builtin(&token[line->i], line);
	}
	if (dup2_in(&fd[0], NULL, 0) == -1 || dup2_out(&fd[1], NULL, 0) == -1)
	{
		cleanup(line, token, 1);
		exit (1);
	}
	close(line->input_fd);
	close(line->output_fd);
}

t_fds	set_path_fds(int check, t_tokens *token, t_mini *line, int prev)
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

void	shell_lvl_check(t_mini *line, t_tokens *token)
{
	char	*shell_value;
	int		value;
	char	*str;
	char	*str_to_export;

	shell_value = get_env_value(line->envp, "SHLVL", line, token);
	value = ft_atoi(shell_value);
	value++;
	str = ft_itoa(value);
	if (!str)
		malloc_failure(line, token);
	str_to_export = ft_strjoin("SHLVL=", str);
	if (!str_to_export)
		malloc_failure(line, token);
	export(str_to_export, line, token);
	free(str);
	free(str_to_export);
}

void	wait_for_child(t_mini *line, t_tokens *token)
{
	int	status;

	line->i = 0;
	status = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	if (token[line->i].command[0] != NULL && \
	ft_strncmp(token[line->i].command[0], "./minishell", 12))
		signal(SIGQUIT, handle_sigquit);
	while (line->i < line->pipe_num)
	{
		if (line->flag == 0)
		{
			wait(&status);
			if (WIFEXITED(status))
				line->err_num = WEXITSTATUS(status);
		}
		line->i++;
	}
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}
