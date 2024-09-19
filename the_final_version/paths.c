/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:02:36 by tparratt          #+#    #+#             */
/*   Updated: 2024/07/15 17:15:40 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**create(char **tokens, char **envp, t_mini *line, t_tokens *token)
{
	char	*path_pointer;
	char	**paths;
	int		i;

	path_pointer = get_env_value(envp, "PATH", line, token);
	if (!path_pointer)
		return (NULL);
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
	if (!paths)
		return (-1);
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
	return (-1);
}

static void	path_error(char *str, char **tokens, t_mini *line, t_tokens *token)
{
	line->err_num = 127;
	print_error(str, tokens);
	tokens[0][0] = 9;
	unnecessary_path(line, token);
}

static int	file_or_directory(char **tokens, t_mini *line, t_tokens *token)
{
	int	fd;

	if (access(tokens[0], F_OK) == 0)
	{
		fd = open(tokens[0], O_RDONLY | O_DIRECTORY);
		if (fd == -1)
		{
			line->paths[line->i] = ft_strdup(tokens[0]);
			if (!line->paths[line->i])
				return (-1);
		}
		else
		{
			path_error("Is a directory", tokens, line, token);
			line->err_num = 126;
		}
	}
	else
		path_error("No such file or directory", tokens, line, token);
	return (0);
}

int	get_path(char **tokens, t_mini *line, t_tokens *token)
{
	char	**paths;

	if (!ft_strncmp(tokens[0], ".", 2))
	{
		path_error("filename argument required", tokens, line, token);
		line->err_num = 2;
		return (0);
	}
	if (!ft_strncmp(tokens[0], "..", 3))
	{
		path_error("command not found", tokens, line, token);
		return (0);
	}
	if (ft_strchr(tokens[0], '/'))
	{
		if (file_or_directory(tokens, line, token) == -1)
			return (-1);
		return (0);
	}
	paths = create(tokens, line->envp, line, token);
	if (!paths || check_access(paths, line, token) != 0)
		path_error("command not found", tokens, line, token);
	return (0);
}
