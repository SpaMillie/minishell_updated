/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:41:22 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/19 12:06:09 by tparratt         ###   ########.fr       */
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
		malloc_failure(line);
	i = 0;
	j = 0;
	while (line->envp[i])
	{
		if (ft_strncmp(line->envp[i], arg, ft_strlen(arg)))
		{
			new_envp[j] = ft_strdup(line->envp[i]);
			if (!new_envp[j])
				malloc_failure(line);
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
	free_2d(line->envp);
	line->envp = new_envp;
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
