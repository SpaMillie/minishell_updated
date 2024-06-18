/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:47:13 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/14 19:59:00 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *str)
{
	if (!ft_strncmp(str, "echo", 5))
		return (1);
	else if (!ft_strncmp(str, "pwd", 4))
		return (1);
	else if (!ft_strncmp(str, "cd", 3))
		return (1);
	else if (!ft_strncmp(str, "env", 4))
		return (1);
	else if (!ft_strncmp(str, "exit", 5))
		return (1);
	else if (!ft_strncmp(str, "export", 7))
		return (1);
	else if (!ft_strncmp(str, "unset", 6))
		return (1);
	else
		return (0);
}

void	execute_builtin(t_tokens *token, t_mini *line)
{
	if (!ft_strncmp(token->command[0], "echo", 5))
		echo(token->command);
	else if (!ft_strncmp(token->command[0], "pwd", 4))
		pwd();
	else if (!ft_strncmp(token->command[0], "cd", 3))
		cd(token->command, line);
	else if (!ft_strncmp(token->command[0], "env", 4))
		env(token->command, line);
	else if (!ft_strncmp(token->command[0], "exit", 5))
		exit_cmd(token->command, line);
	else if (!ft_strncmp(token->command[0], "export", 7))
		export_cmd(token->command, line);
	else if (!ft_strncmp(token->command[0], "unset", 6))
		unset_cmd(token->command, line);
}
