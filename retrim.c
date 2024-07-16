/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrim.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:08:21 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/16 17:20:18 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*retrim_copy(char *s)
{
	int		i;

	i = 0;

    while (s[i] != '\0')
    {
        if (s[i] == PIPE)
            s[i] = '|';
        else if (s[i] == RED_OUT)
            s[i] = '>';
        else if (s[i] == RED_IN)
            s[i] = '<';
        i++;
    }
	return (s);
}

void    retrim_tokens(t_tokens *token)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (token->command[i] != NULL)  
    {
        token->command[i] = retrim_copy(token->command[i]);
        i++;
    }
    if (token->redirect[j] != NULL)
    {
        while (token->redirect[j] != NULL)
        {
            j++;
            token->redirect[j] = retrim_copy(token->redirect[j]);
            j++;
        }
    }
}
