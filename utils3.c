/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:38:12 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/10 14:38:02 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_close(t_mini *line, t_tokens *token)
{			
	ft_putendl_fd("minishell: error while closing a file", 2);
	cleanup(line, token, 1);
	exit (1);
}

int has_input(t_tokens *token)
{
    int i;

    i = 0;
    while (token->redirect[i])
	{
		if ((ft_strncmp(token->redirect[i], "<", 2) == 0)
			|| (ft_strncmp(token->redirect[i], "<<", 3) == 0))
			return (1);
        else
            i += 2;
	}
    return (0);
}

int has_output(t_tokens *token)
{
    int i;

    i = 0;
    while (token->redirect[i])
	{
		if ((ft_strncmp(token->redirect[i], ">", 2) == 0)
			|| (ft_strncmp(token->redirect[i], ">>", 3) == 0))
			return (1);
        else
            i += 2;
	}
    return (0);
}

int	empty_command(t_mini *line, char *line_read)
{
	free_2d(line->element);
	free_2d(line->metaed);
	free(line_read);
	return (1);
}

void	unnecessary_path(t_mini *line, t_tokens *token)
{
	line->paths[line->i] = ft_strdup("won't be used\n");
	if (!line->paths[line->i])
		malloc_failure(line, token);	
}
