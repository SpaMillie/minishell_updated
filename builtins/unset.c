/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:41:22 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/10 15:10:14 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset(char *arg, t_mini *line)
{
	char	**new_envp;
	int		i;
	int		j;

	new_envp = malloc_2d(line->envp);
	if (!new_envp)
		malloc_failure();
	i = 0;
	j = 0;
	while (line->envp[i])
	{
		if (ft_strncmp(line->envp[i], arg, ft_strlen(arg)))
		{
			new_envp[j] = ft_strdup(line->envp[i]);
			if (!new_envp[j])
				malloc_failure();
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
	free_2d(line->envp);
	line->envp = new_envp;
}

int	export_unset_error_check(char **args, t_mini *line)
{
	int	i;
	int	j;

	i = 1;
	if (ft_isdigit(args[i][0]))
	{
		line->err_num = 1;
		print_error("not a valid identifier", args);
		return (1);
	}
	while (args[i])
	{
		j = 0;
		if ((!ft_isalnum(args[i][j]) && args[i][j] != '_'))
		{
			line->err_num = 1;
			print_error("not a valid identifier", args);
			return (1);
		}
		i++;
	}
	return (0);
}

void	unset_cmd(char **args, t_mini *line)
{
	int	i;

	if (!args[1])
		return ;
	else
	{
		if (export_unset_error_check(args, line))
			return ;
		i = 1;
		while (args[i])
		{
			unset(args[i], line);
			i++;
		}
	}
}
