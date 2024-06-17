/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:21:50 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/13 15:06:33 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_len(char *s, int start, int len)
{
	if (s[start - 1] == '$') // something in this if clause to fix
	{
		while (s[len] != '$' && s[len] != '\0' && (ft_isalnum(s[len])
				|| s[len] == '_' || s[len] == '?' || is_whitespace(s[len])))
		{
			len++;
			if (s[len] == '?')
				break ;
		}
	}
	else
	{
		while (s[len] != '$' && s[len] != '\0')
			len++;
	}
	len = len - start;
	return (len);
}

char	*get_substring(char *s, int j)
{
	int		start;
	int		len;
	char	*substring;

	start = j;
	len = j;
	len = get_len(s, start, len);
	substring = ft_substr(s, start, len);
	if (!substring)
		malloc_failure();
	return (substring);
}

void	dup_or_join(char **new_tokens, int loop, int i, char *str)
{
	if (loop == 0)
		new_tokens[i] = ft_strdup(str);
	else
		new_tokens[i] = join_and_free(new_tokens[i], str);
	ft_printf("new_tokens = %s\n", new_tokens[i]);
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
		malloc_failure();
}