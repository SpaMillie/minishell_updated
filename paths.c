/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:02:36 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/12 15:14:04 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_paths(char **tokens, char **envp)
{
	char	*path_pointer;
	char	**paths;
	int		i;

	path_pointer = ft_getenv(envp, "PATH");
	if (!path_pointer)
		return (NULL);
	paths = ft_split(path_pointer, ':');
	if (!paths)
		return (NULL);
	free(path_pointer);
	i = 0;
	while (paths[i])
	{
		paths[i] = join_and_free(paths[i], "/");
		paths[i] = join_and_free(paths[i], tokens[0]);
		i++;
	}
	return (paths);
}

static char	*check_access(char **paths)
{
	int		i;
	char	*res;

	i = 0;
	res = NULL;
	while (paths[i])
	{
		if (access(paths[i], F_OK) == 0)
		{
			res = ft_strdup(paths[i]);
			if (!res)
				exit(1);
			free_2d(paths);
			return (res);
		}
		i++;
	}
	return (res);
}

char	*get_path(char **tokens, char **envp)
{
	char	*res;
	char	**paths;

	if (!ft_strncmp(tokens[0], "./", 2))
	{
		res = ft_strdup(tokens[0]);
		if (!res)
			malloc_failure();
		return (res);
	}
	paths = create_paths(tokens, envp);
	if (!paths)
		return (NULL);
	res = check_access(paths);
	if (res)
		return (res);
	free_2d(paths);
	print_error("command not found", tokens);
	return (NULL);
}
