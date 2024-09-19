/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:27:29 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/17 14:44:07 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_i(char *s, int i)
{			
	while (s[i] != '\0' && is_it_space(s, i) != 0)
	{
		if (s[i] == '\'' || s[i] == '\"')
			i = ft_skip(s, i);
		else
			i++;
	}
	return (i);
}

static void	first_splitting(char *s, t_mini *line)
{
	int	j;
	int	i;
	int	prev_i;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && is_it_space(s, i) == 0)
			i++;
		if (s[i] != '\0' && is_it_space(s, i) != 0)
		{
			prev_i = i;
			if (s[i] != '\0' && is_it_space(s, i) != 0)
				i = get_i(s, i);
			line->element[j++] = ft_substr(s, prev_i, i - prev_i);
			if (line->element[j - 1] == NULL)
				malloc_failure_without_token(line);
		}
	}
	line->element[j] = NULL;
}

static int	e_count(char *s)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && is_it_space(s, i) == 0)
			i++;
		if (s[i] != '\0' && is_it_space(s, i) != 0)
		{
			words++;
			while (s[i] != '\0' && is_it_space(s, i) != 0)
			{
				if (s[i] == '\'' || s[i] == '\"')
					i = ft_skip(s, i);
				else
					i++;
				if (i == -1)
					return (-1);
			}
		}
	}
	return (words);
}

int	first_split(char *argv, t_mini *line)
{
	int	words;

	words = e_count(argv);
	if (words == -1)
		return (-1);
	line->element = (char **)malloc(sizeof(char *) * (words + 1));
	if (!line->element)
		malloc_failure_without_token(line);
	first_splitting(argv, line);
	return (0);
}
