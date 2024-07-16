/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:59:50 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/16 18:05:42 by tparratt         ###   ########.fr       */
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
	opening(&token[line->i], line); //in opening it returns -1 if its an error but thats important for forking only
	unnecessary_path(line, token);
	cur = set_fds(line, &token[line->i], &fd[0]);
	redirections(line, &token[line->i], &cur);
	if (line->input_fd != -1 && line->output_fd != -1)
	{
		line->err_num = 0;
		execute_builtin(&token[line->i], line); // Execute the built-in
	}
	if (dup2_in(&fd[0], NULL, 0) == -1 || dup2_out(&fd[1], NULL, 0) == -1)
	{
		cleanup(line, token, 1);
		exit(1);	
	}
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

void	wait_for_child(t_mini *line)
{
	int	status;

	line->i = 0;
	status = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, handle_sigint);
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
	check_g_sigflag(line);
}
