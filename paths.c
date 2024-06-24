/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milica <milica@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:02:36 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/24 16:13:59 by milica           ###   ########.fr       */
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
		return (NULL); //is this a malloc fail?
	paths = ft_split(path_pointer, ':');
	if (!paths)
		return (NULL);
	free(path_pointer);
	i = 0;
	while (paths[i])
	{
		paths[i] = join_and_free(paths[i], "/");
		paths[i] = join_and_free(paths[i], tokens[0]);
		if (!paths[i])
			return (NULL);
		i++;
	}
	return (paths);
}

static int	check_access(char **paths, t_mini *line)
{
	int		i;

	i = 0;
	while (paths[i])
	{
		if (access(paths[i], F_OK) == 0)
		{
			line->paths[line->i] = ft_strdup(paths[i]);
			free_2d(paths);
			if (!(line->paths[line->i]))
				malloc_failure(line);
			return (0);
		}
		i++;
	}
	free_2d(paths);
	line->paths[line->i] = ft_strdup(NULL);
	return (-1);
}

int	get_path(char **tokens, t_mini *line)
{
	char	**paths;

	if (ft_strchr(tokens[0], '/'))
	{
		if (access(tokens[0], F_OK) == 0)
		{
			line->paths[line->i] = ft_strdup(tokens[0]);
			if (!line->paths[line->i])
			 	return (-1);
		}
		else
			print_error("No such file or directory", tokens);
		return (0);
	}
	printf("malloced paths\n");
	paths = create_paths(tokens, line->envp);
	if (!paths)
		return (-1);
	if (check_access(paths, line) != 0)
	{
		tokens[0][0] = 9;
		print_error("command not found", tokens);
	}
	return (0);
}
