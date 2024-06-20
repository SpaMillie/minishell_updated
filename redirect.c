/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid Date        by              +#+  #+#    #+#             */
/*   Updated: 2024/06/20 15:28:01 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static void	redirect_output_append(t_tokens *token, int j)
{
	int	fd;

	printf("entered redirect_output_append\n");
	fd = open(token->redirect[j + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		printf("error while opening the file\n");
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		printf("dup2 failed\n");
		return ;
	}
	close(fd);
	printf("exited redirect_output_append\n");
}

static void	redirect_output(t_tokens *token, int j)
{
	int	fd;

	printf("entered redirect_output\n");
	fd = open(token->redirect[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("error while opening the file\n");
		return ;
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		printf("dup2 failed\n");
		return ;
	}
	close(fd);
	printf("exited redirect_output\n");
}

static void	redirect_input(t_tokens *token, int j)
{
	int	fd;

	printf("entered redirect_input\n");
	fd = open(token->redirect[j + 1], O_RDONLY);
	if (fd == -1)
	{
		printf("Permission denied or No such file\n");
		return ;
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		printf("dup2 failed\n");
		return ;
	}
	printf("exited redirect_input\n");
	close(fd);
}

void	redirections(t_tokens *token)
{
	int	j;

	j = 0;
	while (token->redirect[j])
	{
		printf("token is %s\n", token->redirect[j]);
		if ((ft_strncmp(token->redirect[j], "<", 2) == 0)
			|| (ft_strncmp(token->redirect[j], "<<", 3) == 0))
			redirect_input(token, j);
		else if (ft_strncmp(token->redirect[j], ">", 2) == 0)
			redirect_output(token, j);
		else if (ft_strncmp(token->redirect[j], ">>", 3) == 0)
			redirect_output_append(token, j);
		j++;
		j++;
	}
}
