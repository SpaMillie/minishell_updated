/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:05:39 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/11 11:45:19 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int    c_count(t_mini *line, t_alloc *ed, int i)
{

    ed->redir = 0;
    ed->other = 0;
    while (line->metaed[i] != NULL)
    {
		if (ft_strlen(line->metaed[i]) != 0 && ft_strncmp(line->metaed[i], "|", ft_strlen(line->metaed[i])) == 0)
			break ;
        else if (is_it_redirect(line->metaed[i]) == 0)
        {
            ed->redir += 2;
            i++;
        }
        else
            ed->other++;
        i++;
    }
	return (i);
}

void    p_count(t_mini *line)
{
    int i;

	i = 0;
    line->pipe_num = 0;
    while (line->metaed[i] != NULL)
    {
        if (ft_strlen(line->metaed[i]) != 0 && ft_strncmp(line->metaed[i], "|", ft_strlen(line->metaed[i])) == 0)
            line->pipe_num++;
        i++;
    }
	line->pipe_num++;
}

static int	allocating_token(t_tokens *token, t_alloc *ed)
{
	token->command = malloc(sizeof(char *) * (ed->other + 1));
	if (!token->command)
		return (-1);
	token->redirect = malloc(sizeof(char *) * (ed->redir + 1));
	if (!token->redirect)
		return (-1);
	return (0);
}

static void	copy_tokens(t_mini *line, t_tokens *token, int pre_i, int i)
{
	int	k;
	int	j;

	k = 0;
	j = 0;
	while (pre_i < i)
	{
        if (is_it_redirect(line->metaed[pre_i]) == 0)
        {
            token->redirect[k++] = ft_strdup(line->metaed[pre_i++]);
			if (!(token->redirect[k - 1]))
				printf("mallocfail 357\n");
            token->redirect[k++] = ft_strdup(line->metaed[pre_i++]);
			if (!(token->redirect[k - 1]))
				printf("mallocfail 360\n");
        }
        else
		{
            token->command[j++] = ft_strdup(line->metaed[pre_i++]);
			if (!(token->command[j - 1]))
				printf("mallocfail 366\n");
		}
	}
    token->redirect[k] = NULL;
	token->command[j] = NULL;
}

void	function(t_mini *line, t_tokens *token)
{
	t_alloc		ed;
	int			prev_i;
	int			i;
	int			j;
	int			check;

	i = 0;
	j = 0;
	check = 0;
	while (j < line->pipe_num)
	{
		prev_i = i;
		i = c_count(line, &ed, i);
		check = allocating_token(&token[j], &ed);
		if (check == -1)
			printf("mallocerror\n");
		copy_tokens(line, &token[j], prev_i, i);
		if (line->metaed[i] != NULL && ft_strncmp(line->metaed[i], "|", ft_strlen(line->metaed[i])) == 0)
			i++;
		j++;
	}
	/*j = 0;
	while (j < line->pipe_num)
	{
		i = 0;
		printf("j is %d\n", j);
		while (token[j].redirect[i] != NULL)
		{
			printf("redirect is: %s\n", token[j].redirect[i]);
			i++;
		}
		i = 0;
		while (token[j].command[i] != NULL)
		{
			printf("command is: %s\n", token[j].command[i]);
			i++;
		}
		j++;
	}*/
}
