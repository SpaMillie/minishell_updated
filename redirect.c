/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:55:18 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/12 15:19:24 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_output_append(t_tokens *token, int j)
{
	int	fd;

	fd = open(token->redirect[j + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1)
		exit(1);
	close(fd);
}

static void	redirect_output(t_tokens *token, int j)
{
	int	fd;

	fd = open(token->redirect[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1 || dup2(fd, STDOUT_FILENO) == -1)
		exit(1);
	close(fd);
}

static void	redirect_input(t_tokens *token, int j)
{
	int	fd;

	fd = open(token->redirect[j + 1], O_RDONLY);
	if (fd == -1 || dup2(fd, STDIN_FILENO) == -1)
		exit(1);
	close(fd);
}

void	redirections(t_tokens *token)
{
	int	j;

	j = 0;
	while (token->redirect[j])
	{
		if ((ft_strncmp(token->redirect[j], "<", 2) == 0)
			|| (ft_strncmp(token->redirect[j], "<<", 3) == 0))
			redirect_input(token, j);
		else if (ft_strncmp(token->redirect[j], ">", 2) == 0)
			redirect_output(token, j);
		else if (ft_strncmp(token->redirect[j], ">>", 3) == 0)
			redirect_output_append(token, j);
		j++;
	}
}
