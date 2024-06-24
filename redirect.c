/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milica <milica@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/24 11:47:25 by milica           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static int	redirect_output_append(t_tokens *token, int j)
{
	int	fd;

	printf("entered redirect_output_append\n");
	fd = open(token->redirect[j + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(token->redirect[j + 1]);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_putendl_fd("minishell: dup2 failed", 2);
		return (-1);
	}
	close(fd);
	printf("exited redirect_output_append\n");
	return (0);
}

static int	redirect_output(t_tokens *token, int j)
{
	int	fd;

	printf("entered redirect_output\n");
	fd = open(token->redirect[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(token->redirect[j + 1]);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		ft_putendl_fd("minishell: dup2 failed", 2);
		return (-1);
	}
	close(fd);
	printf("exited redirect_output\n");
	return (0);
}

static int	redirect_input(t_tokens *token, int j)
{
	int	fd;

	printf("entered redirect_input\n");
	fd = open(token->redirect[j + 1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(token->redirect[j + 1]);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		ft_putendl_fd("minishell: dup2 failed", 2);
		return (-1);
	}
	printf("exited redirect_input\n");
	close(fd);
	return (0);
}

int	redirections(t_tokens *token)
{
	int	j;
	int	check;

	j = 0;
	while (token->redirect[j])
	{
		printf("token is %s\n", token->redirect[j]);
		if ((ft_strncmp(token->redirect[j], "<", 2) == 0)
			|| (ft_strncmp(token->redirect[j], "<<", 3) == 0))
			check = redirect_input(token, j);
		else if (ft_strncmp(token->redirect[j], ">", 2) == 0)
			check = redirect_output(token, j);
		else if (ft_strncmp(token->redirect[j], ">>", 3) == 0)
			check = redirect_output_append(token, j);
		if (check == -1)
			return (check);
		j++;
		j++;
	}
	return (0);
}
