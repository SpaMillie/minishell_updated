/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:39:35 by mspasic           #+#    #+#             */
/*   Updated: 2024/06/15 15:13:13 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2d(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	malloc_failure(t_mini *line)
{
	ft_putendl_fd("minishell: malloc failure", 2);
    free_2d(line->element);
    free_2d(line->metaed);
	//free everything
	exit(1);
}

void	void_malloc_failure(void)
{
	ft_putendl_fd("minishell: malloc failure", 2);
	exit(1);
}

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
			malloc_failure(line);
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
