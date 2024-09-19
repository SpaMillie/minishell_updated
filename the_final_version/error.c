/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 13:39:35 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/17 14:47:07 by mspasic          ###   ########.fr       */
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

void	malloc_failure_without_token(t_mini *line)
{
	ft_putendl_fd("minishell: malloc failure", 2);
	free_2d(line->element);
	free_2d(line->metaed);
	if (line->paths)
		free_2d(line->paths);
	free_2d(line->envp);
	exit(1);
}

void	malloc_failure(t_mini *line, t_tokens *token)
{
	ft_putendl_fd("minishell: malloc failure", 2);
	cleanup(line, token, 1);
	exit(1);
}

void	malloc_failure_no_cleanup(void)
{
	ft_putendl_fd("minishell: malloc failure", 2);
	exit(1);
}
