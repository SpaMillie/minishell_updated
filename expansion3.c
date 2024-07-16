/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:49:06 by tparratt          #+#    #+#             */
/*   Updated: 2024/07/16 17:51:59 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_or_join(char **new_tokens, int loop, int i, char *str)
{
	if (loop == 0)
		new_tokens[i] = ft_strdup(str);
	else
		new_tokens[i] = join_and_free(new_tokens[i], str);
	if (!new_tokens[i])
		return (1);
	return (0);
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
		malloc_failure_without_token(line);
}
