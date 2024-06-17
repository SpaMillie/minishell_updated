/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:50:13 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/12 14:52:53 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char **envp, char *str, t_mini *line)
{
	char	*env;
	char	*env_value;
	int		i;

	if (!ft_strncmp(str, "?", 2))
	{
		env_value = ft_strdup(ft_itoa(line->err_num));
		return (env_value);
	}
	env = ft_getenv(envp, str);
	if (!env)
		return (NULL);
	i = 0;
	while (env[i] != '=')
		i++;
	i++;
	env_value = ft_substr(env, i, ft_strlen(env));
	return (env_value);
}

char	*ft_getenv(char **envp, char *str)
{
	int		i;
	char	*path_pointer;
	int		j;
	int		len;

	i = 0;
	j = 0;
	path_pointer = NULL;
	len = ft_strlen(str);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], str, len) && envp[i][len] == '=')
		{
			path_pointer = ft_strdup(envp[i]);
			if (!path_pointer)
				malloc_failure();
			break ;
		}
		i++;
	}
	if (!path_pointer)
		return (NULL);
	return (path_pointer);
}
