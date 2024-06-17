/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validating.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:27:51 by tparratt          #+#    #+#             */
/*   Updated: 2024/05/31 12:10:26 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_skip(char *s, int i)
{
	char	c;

	c = s[i];
	i++;
	while (s[i] != '\0' && s[i] != c)
		i++;
	if (s[i] == c)
		return (i + 1);
	else
		return (-1);
}

static int	w_count(char *s)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while(s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == 32) //add whitespace cchars
			i++;
		if (s[i] == '\'' || s[i] == '\"')
		{
			i = ft_skip(s, i);
			if (i == -1)
				return (-1);
		}
		else if (s[i] == '|' || s[i] == '>' || s[i] == '<')
		{
			if (s[i] != '|' && (s[i + 1] == '>' || s[i + 1] == '<'))
				i++;
			i++;
		}
		else
		{
			while (s[i] != '\0' && ft_strchr(" >|<\'\"", s[i]) == NULL)
				i++;
		}
		words++;
	}
	return (words);
}

static void	minishell_split(char *s, t_mini *line)
{
	int	i;
	int	j;
	int	prev_i;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == 32)
			i++;
		prev_i = i;
		if (s[i] == '\'' || s[i] == '\"')
			i = ft_skip(s, i);
		else if (s[i] == '|' || s[i] == '>' || s[i] == '<')
		{
			if ((s[i] == '<' && s[i + 1] == '<') || (s[i] == '>' && s[i + 1] == '>'))
				i++;
			i++;
		}
		else
		{
			while (s[i] != '\0' && ft_strchr(" >|<\'\"", s[i]) == NULL)
				i++;
		}
		if (prev_i != i)
		{
			line->metaed[j++] = ft_substr(s, prev_i, i - prev_i);
			if (line->metaed[j - 1] == NULL)
				printf("malloc error\n");
		}
	}
	line->metaed[j] = NULL;
}

int	is_it_redirect(char *s)
{
	int	len;

	len = ft_strlen(s);
	if (len != 0 && (ft_strncmp(s, "<", len) == 0 || ft_strncmp(s, ">", len) == 0 || \
			ft_strncmp(s, ">>", len) == 0 || ft_strncmp(s, "<<", len) == 0))
		return (0);
	return (-1);
}

void	validating(char *argv, t_mini *line)
{
	int	words;
	int	i;

	i = 0;
	words = w_count(argv);
	if (words == -1)
		printf("zsh: could not find the matching quote\n");
	line->metaed = (char **)malloc(sizeof(char *) * (words + 1));
	if (!line->metaed)
		printf("zsh: Cannot allocate memory\n");
	minishell_split(argv, line);
	if (ft_strncmp(line->metaed[0], "|", ft_strlen(line->metaed[0])) == 0)
		printf("zsh: parse error near `|'\n");
	while (i + 1 < words)
	{
		if (is_it_redirect(line->metaed[i]) == 0 && is_it_redirect(line->metaed[i + 1]) == 0)
			printf("zsh: parse error near i + 1\n"); //needs a function to output the second redirection
		i++;
	}
	if (ft_strncmp(line->metaed[i], "|", ft_strlen(line->metaed[i])) == 0 || \
		(is_it_redirect(line->metaed[i]) == 0))
		printf("zsh: parse error near \\n\n");
}
