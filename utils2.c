/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milica <milica@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:51:42 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/25 10:37:23 by milica           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup(t_mini *line, t_tokens *token, int option)
{
	int	i;

	i = 0;
	free_2d(line->element);
	free_2d(line->metaed);
	if (line->paths)
	{
		while (i < line->pipe_num)
			free(line->paths[i++]);
		free(line->paths);
	}
	if (option)
		free_2d(line->envp);
	i = 0;
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

	if (!prompt)
		return (NULL); //if the previous join_and_free failed
	temp = ft_strjoin(prompt, str);
	free(prompt);
	if (!temp)
	{
		//malloc_fail?
		return (NULL);
	}
	prompt = temp;
	return (prompt);
}
