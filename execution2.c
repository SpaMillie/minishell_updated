/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:59:50 by mspasic           #+#    #+#             */
/*   Updated: 2024/06/20 15:06:24 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_builtin(t_tokens *token, t_mini *line, int *fd)
{		
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	redirections(&token[line->i]);
	builtin_execution(token, line);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	return ;
}

void	shell_lvl_check(t_mini *line)
{
	char	*shell_value;
	int		value;
	char	*str;
	char	*str_to_export;

	shell_value = get_env_value(line->envp, "SHLVL", line);
	value = ft_atoi(shell_value);
	value++;
	str = ft_itoa(value);
	if(!str)
		malloc_failure(line);
	str_to_export = ft_strjoin("SHLVL=", str);
	if(!str_to_export)
		malloc_failure(line);
	export(str_to_export, line);
	free(str);
	free(str_to_export);
}

void	wait_for_child(t_mini *line)
{
	int	status;

	line->i = 0;
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
}
