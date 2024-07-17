/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:51:42 by tparratt          #+#    #+#             */
/*   Updated: 2024/07/17 14:50:52 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unlink_heredoc(t_mini *line, t_tokens *token)
{
	int	i;
	int	j;

	i = 0;
	while (i < line->pipe_num)
	{
		j = 0;
		while (token[i].redirect[j] != NULL)
		{
			if (ft_strncmp(token[i].redirect[j], "<<", 3) == 0)
			{
				unlink(token[i].redirect[j + 1]);
			}
			j++;
			j++;
		}
		i++;
	}
}

void	free_paths(t_mini *line)
{
	int	i;

	i = 0;
	while (i < line->pipe_num)
		free(line->paths[i++]);
	free(line->paths);
}

void	cleanup(t_mini *line, t_tokens *token, int option)
{
	int	i;

	i = 0;
	free_2d(line->element);
	free_2d(line->metaed);
	free_paths(line);
	if (option != 0)
		free_2d(line->envp);
	unlink_heredoc(line, token);
	while (i < line->pipe_num)
	{
		free_2d(token[i].command);
		free_2d(token[i].redirect);
		i++;
	}
	free(token);
}

void	print_2d(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf("%s\n", tab[i]);
		i++;
	}
}

char	*join_and_free(char *prompt, char *str)
{
	char	*temp;

	temp = ft_strjoin(prompt, str);
	free(prompt);
	if (!temp)
		return (NULL);
	prompt = temp;
	return (prompt);
}
