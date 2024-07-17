/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   second_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:00:50 by tparratt          #+#    #+#             */
/*   Updated: 2024/07/17 14:40:16 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_it_meta(char c, char other_c, int option)
{
	if (c == '>' || c == '<' || c == '|')
	{
		if (option == 0)
			return (1);
		else
		{
			if ((c == '<' && other_c == '<') || (c == '>' && other_c == '>'))
				return (1);
			return (0);
		}
	}
	return (0);
}

static void	split_single(t_mini *line, char *s, int i)
{
	int	prev_i;

	while (s[i] != '\0')
	{
		prev_i = i;
		if (is_it_meta(s[i], s[i + 1], 0))
		{
			if (is_it_meta(s[i], s[i + 1], 1))
				i++;
			i++;
		}
		else
		{
			while (s[i] != '\0' && !is_it_meta(s[i], s[i + 1], 0))
			{
				if (s[i] == '\'' || s[i] == '\"')
					i = ft_skip(s, i);
				else
					i++;
			}
		}
		line->metaed[line->i++] = ft_substr(s, prev_i, i - prev_i);
		if (line->metaed[line->i - 1] == NULL)
			malloc_failure_without_token(line);
	}
}

static void	second_splitting(t_mini *line)
{
	int	i;

	i = 0;
	line->i = 0;
	while (line->element[i] != NULL)
	{
		split_single(line, line->element[i], 0);
		i++;
	}
	line->metaed[line->i] = NULL;
}

static int	w_count(char *s, int words)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (is_it_meta(s[i], s[i + 1], 0))
		{
			if (is_it_meta(s[i], s[i + 1], 1))
				i++;
			i++;
			words++;
		}
		else
		{
			while (s[i] != '\0' && !is_it_meta(s[i], s[i + 1], 0))
			{
				if (s[i] == '\'' || s[i] == '\"')
					i = ft_skip(s, i);
				else
					i++;
			}
			words++;
		}
	}
	return (words);
}

int	second_split(t_mini *line)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (line->element[i] != NULL)
	{
		words = w_count(line->element[i], words);
		i++;
	}
	line->metaed = (char **)malloc(sizeof(char *) * (words + 1));
	if (!line->metaed)
		malloc_failure_without_token(line);
	second_splitting(line);
	return (words);
}
