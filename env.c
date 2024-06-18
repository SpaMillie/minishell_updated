/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:50:13 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/17 15:51:08 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*err_num_value(t_mini *line)
{
	char	*itoaed_err_num;
	char	*err_num_value;
	
	itoaed_err_num = ft_itoa(line->err_num);
	if (!itoaed_err_num)
		malloc_failure(line);
	err_num_value = ft_strdup(itoaed_err_num);
	if (!err_num_value)
		malloc_failure(line);
	free(itoaed_err_num);
	return (err_num_value);
}

char	*get_env_value(char **envp, char *str, t_mini *line)
{
	char	*env;
	char	*env_value;
	int		i;

	if (!ft_strncmp(str, "?", 2))
	{
		env_value = err_num_value(line);
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
	if (!env_value)
		malloc_failure(line);
	return (env_value);
}

char	*ft_getenv(char **envp, char *str)
{
	int		i;
	char	*path_pointer;
	int		len;

	i = 0;
	path_pointer = NULL;
	len = ft_strlen(str);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], str, len) && envp[i][len] == '=')
		{
			path_pointer = ft_strdup(envp[i]);
			if (!path_pointer)
				void_malloc_failure();
			break ;
		}
		i++;
	}
	if (!path_pointer)
		return (NULL);
	return (path_pointer);
}
