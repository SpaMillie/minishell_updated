/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:02:36 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/24 14:49:17 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create_paths(char **tokens, char **envp, t_mini *line, t_tokens *token)
{
	char	*path_pointer;
	char	**paths;
	int		i;

	path_pointer = ft_getenv(envp, "PATH", line, token);
	if (!path_pointer)
		malloc_failure(line, token);
	paths = ft_split(path_pointer, ':');
	if (!paths)
		malloc_failure(line, token);
	free(path_pointer);
	i = 0;
	while (paths[i])
	{
		paths[i] = join_and_free(paths[i], "/");
		paths[i] = join_and_free(paths[i], tokens[0]);
		if (!paths[i])
			malloc_failure(line, token);
		i++;
	}
	return (paths);
}

static char	*check_access(char **paths, t_mini *line, t_tokens *token)
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
				malloc_failure(line, token);
			free_2d(paths);
			return (res);
		}
		i++;
	}
	return (res);
}

char	*get_path(char **tokens, char **envp, t_mini *line, t_tokens *token)
{
	char	*res;
	char	**paths;

	if (ft_strchr(tokens[0], '/'))
	{
		if (access(tokens[0], F_OK) == 0)
			return(tokens[0]);
		else
		{
			print_error("No such file or directory", tokens);
			return (NULL);
		}
	}
	paths = create_paths(tokens, envp, line, token);
	if (!paths)
		return (NULL);
	res = check_access(paths, line, token);
	if (res)
		return (res);
	free_2d(paths);
	print_error("Command not found", tokens);
	return (NULL);
}
