/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:31:15 by tparratt          #+#    #+#             */
/*   Updated: 2024/07/16 12:34:11 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*nothing_to_expand(t_mini *line, char **new_tokens, int loop, int j)
{
	char	*substring;

	substring = get_substring(line->metaed[line->i], j);
	if (dup_or_join(new_tokens, loop, line->i, substring))
		malloc_failure_without_token(line);
	return (substring);
}

static char	*substring_expand(t_mini *line, char **new_tokens, int loop, int *j)
{
	char	*substring;
	char	*env_value;

	(*j)++;
	substring = get_substring(line->metaed[line->i], *j);
	env_value = get_env_value(line->envp, substring, line, NULL);
	if (!env_value)
	{
		if (dup_or_join(new_tokens, loop, line->i, ""))
			malloc_failure_without_token(line);
	}
	else
	{
		if (dup_or_join(new_tokens, loop, line->i, env_value))
			malloc_failure_without_token(line);
	}
	free(env_value);
	return (substring);
}

static void	dollars_only(t_mini *line, char **new_tokens, int *loop, int *j)
{
	if (dup_or_join(new_tokens, *loop, line->i, "$"))
		malloc_failure_without_token(line);
	(*j)++;
	(*loop)++;
}

static void	expand(t_mini *line, char **new_tokens)
{
	int		j;
	int		loop;
	char	*substring;
	char	*metaed;

	j = 0;
	loop = 0;
	metaed = line->metaed[line->i];
	while (metaed[j])
	{
		ft_printf("entered expansion loop\n");
		if (metaed[j] == '$' && (!ft_isalnum(metaed[j + 1])
				&& metaed[j + 1] != '_' && metaed[j + 1] != '?')) // dollars only
		{
			ft_printf("dollars only\n");
			dollars_only(line, new_tokens, &loop, &j);
			continue ;
		}
		else if (metaed[j] == '$' && (ft_isalnum(metaed[j + 1])
				|| metaed[j + 1] == '_' || metaed[j + 1] == '?'))
			substring = substring_expand(line, new_tokens, loop, &j);
		else
		{
			ft_printf("nothing to expand\n");
			substring = nothing_to_expand(line, new_tokens, loop, j);
		}
		j += ft_strlen(substring);
		free(substring);
		loop++;
	}
}

void	expansion(t_mini *line)
{
	char	**new_tokens;

	line->i = 0;
	new_tokens = malloc_2d(line->metaed);
	if (!new_tokens)
		malloc_failure_without_token(line);
	while (line->metaed[line->i])
	{
		ft_printf("line->metaed = %s\n", line->metaed[line->i]);
		if (ft_strchr(line->metaed[line->i], '$'))
			expand(line, new_tokens);
		else
			duplicate(line, new_tokens);
		if (line->metaed[line->i][0] == '$')
		{
			ft_printf("HELLO\n");
			new_tokens[line->i] = ft_substr(line->metaed[line->i], 1, ft_strlen(line->metaed[line->i]));
		}
		line->i++;
	}
	new_tokens[line->i] = NULL;
	free_2d(line->metaed);
	line->metaed = new_tokens;
}
