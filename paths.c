/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milica <milica@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:02:36 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/25 10:30:15 by milica           ###   ########.fr       */
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

static int	check_access(char **paths, t_mini *line, t_tokens *token)
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
				malloc_failure(line, token);
			return (0);
		}
		i++;
	}
	free_2d(paths);
	line->paths[line->i] = ft_strdup("");
	return (-1);
}

int	get_path(char **tokens, t_mini *line, t_tokens *token)
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
	paths = create_paths(tokens, line->envp, line, token);
	if (!paths)
		return (-1);
	if (check_access(paths, line, token) != 0)
	{
		print_error("command not found", tokens);
		tokens[0][0] = 9;
	}
	return (0);
}
