/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:21:50 by tparratt          #+#    #+#             */
/*   Updated: 2024/07/16 17:51:49 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	otherwise(char *s, int len)
{
	while (s[len] != '$' && s[len] != '\0')
		len++;
	return (len);
}

static int	get_len(char *s, int start, int len)
{
	if (start > 0 && s[start - 1] == '$')
	{
		if (s[len] == '\'' || s[len] == '"')
			len++;
		if (!is_it_space(s, len))
		{
			while (s[len] != '$' && s[len] != '\0' && (ft_isalnum(s[len])
					|| s[len] == '_' || s[len] == '?' || !is_it_space(s, len)))
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
		len = otherwise(s, len);
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
		exit(1);
	return (substring);
}

char	*nothing_to_expand(t_mini *line, char **new_tokens, int loop, int j)
{
	char	*substring;

	substring = get_substring(line->metaed[line->i], j);
	if (dup_or_join(new_tokens, loop, line->i, substring))
		malloc_failure_without_token(line);
	return (substring);
}
