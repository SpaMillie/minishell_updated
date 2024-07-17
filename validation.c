/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:48:57 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/17 12:52:50 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_it_space(char *s, int i)
{
	if ((s[i] == 32 || (s[i] < 14 && s[i] > 8)))
		return (0);
	return (1);
}

int	ft_skip(char *s, int i)
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

int	is_it_redirect(char *s)
{
	if (ft_strncmp(s, "<", 2) == 0 || ft_strncmp(s, ">", 2) == 0 || \
		ft_strncmp(s, ">>", 3) == 0 || ft_strncmp(s, "<<", 3) == 0)
		return (0);
	return (-1);
}

int	validating(char *argv, t_mini *line, char *line_read)
{
	int	words;
	int	i;

	i = 0;
	if (first_split(argv, line) == -1)
		return (syntax_error(line, NULL, 1));
	words = second_split(line);
	if (line->metaed[i] == NULL)
		return (empty_command(line, line_read));
	if (check_syntax_errors(line, words) == 1)
		return (1);
	trim_quotes(line);
	if (here_doc(line))
		return (1);
	return (0);
}
