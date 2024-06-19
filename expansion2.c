/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:21:50 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/19 14:28:21 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_len(char *s, int start, int len)
{
	if (start > 0 && s[start - 1] == '$')
	{
		if (is_whitespace(s[len]))
		{
			while (s[len] != '$' && s[len] != '\0' && (ft_isalnum(s[len])
					|| s[len] == '_' || s[len] == '?' || is_whitespace(s[len])))
				len++;
		}
		else
		{
			while (s[len] != '$' && s[len] != '\0' && (ft_isalnum(s[len])
					|| s[len] == '_' || s[len] == '?'))
			{
				len++;
				if ((s[len] == '?' && s[len - 1] == '?')
					|| (ft_isalnum(s[len]) && s[len - 1] == '?'))
					break ;
			}
		}
	}
	else
		while (s[len] != '$' && s[len] != '\0')
			len++;
	return (len - start);
}

char	*get_substring(char *s, int j)
{
	int		start;
	int		len;
	char	*substring;

	start = j;
	len = j;
	if (start < 0 || start >= (int)ft_strlen(s))
		return (ft_strdup(""));
	len = get_len(s, start, len);
	substring = ft_substr(s, start, len);
	if (!substring)
		void_malloc_failure();
	return (substring);
}

void	dup_or_join(char **new_tokens, int loop, int i, char *str)
{
	if (loop == 0)
	{
		new_tokens[i] = ft_strdup(str);
		if (!new_tokens[i])
			void_malloc_failure();
	}
	else
		new_tokens[i] = join_and_free(new_tokens[i], str);
}

void	duplicate(t_mini *line, char **new_tokens)
{
	int	j;

	if (ft_strchr(line->metaed[line->i], 7))
	{
		j = 0;
		while (line->metaed[line->i][j])
		{
			if (line->metaed[line->i][j] == 7)
				line->metaed[line->i][j] = '$';
			j++;
		}
	}
	new_tokens[line->i] = ft_strdup(line->metaed[line->i]);
	if (!new_tokens[line->i])
		malloc_failure(line);
}
