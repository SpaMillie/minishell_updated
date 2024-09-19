/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:41:22 by tparratt          #+#    #+#             */
/*   Updated: 2024/07/19 14:41:37 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset(char *arg, t_mini *line, t_tokens *token)
{
	char	**new_envp;
	int		i;
	int		j;

	new_envp = malloc_2d(line->envp);
	if (!new_envp)
		malloc_failure(line, token);
	i = 0;
	j = 0;
	while (line->envp[i])
	{
		if (ft_strncmp(line->envp[i], arg, ft_strlen(arg)))
		{
			new_envp[j] = ft_strdup(line->envp[i]);
			if (!new_envp[j])
				malloc_failure(line, token);
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
	free_2d(line->envp);
	line->envp = new_envp;
}

void	unset_cmd(char **args, t_mini *line, t_tokens *token)
{
	int	i;

	if (!args[1])
		return ;
	else
	{
		token[line->i].command = export_unset_error_check(args, line);
		if (!token[line->i].command)
			malloc_failure(line, token);
		i = 1;
		while (args[i])
		{
			if (ft_strlen(args[i]) != 0)
				unset(args[i], line, token);
			i++;
		}
	}
}
