/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 10:38:12 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/09 18:23:17 by mspasic          ###   ########.fr       */
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
