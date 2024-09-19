/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_erors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:41:38 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/17 12:45:32 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error(t_mini *line, char *s, int i)
{
	char	*str;

	if (i == 1)
	{
		ft_putendl_fd("minishell: could not find the matching quote", 2);
		return (1);
	}
	else if (i == 2)
		ft_putendl_fd("minishell: parse error near '|'", 2);
	else if (i == 3)
	{
		str = ft_strjoin("minishell: parse error near ", s);
		if (!str)
			malloc_failure_without_token(line);
		ft_putendl_fd(str, 2);
		free (str);
	}
	else if (i == 4)
		ft_putendl_fd("minishell: parse error near \\n", 2);
	line->err_num = 2;
	free_2d(line->element);
	free_2d(line->metaed);
	return (1);
}

static int	is_it_quotes(char *s)
{
	if (ft_strncmp(s, "\"\"", 3) == 0 || ft_strncmp(s, "''", 3) == 0)
		return (0);
	return (-1);
}

int	check_syntax_errors(t_mini *line, int words)
{
	int	i;

	i = 0;
	if (ft_strlen(line->metaed[i]) != 0 && \
	is_it_quotes(line->metaed[i]) != 0 && \
	ft_strncmp(line->metaed[i], "|", ft_strlen(line->metaed[i])) == 0)
		return (syntax_error(line, NULL, 2));
	while (i + 1 < words)
	{
		if (ft_strlen(line->metaed[i]) != 0 && \
		is_it_quotes(line->metaed[i]) == -1 && \
		is_it_redirect(line->metaed[i]) == 0 && \
		is_it_redirect(line->metaed[i + 1]) == 0)
			return (syntax_error(line, line->metaed[i + 1], 3));
		i++;
	}
	if (ft_strlen(line->metaed[i]) != 0 && \
	is_it_quotes(line->metaed[i]) == -1 && \
	(ft_strncmp(line->metaed[i], "|", ft_strlen(line->metaed[i])) == 0 \
	|| is_it_redirect(line->metaed[i]) == 0))
		return (syntax_error(line, NULL, 4));
	return (0);
}
