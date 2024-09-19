/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opening_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:03:35 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/17 12:16:04 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_output_append(t_mini *line, t_tokens *token, int j)
{
	int	fd;

	fd = open(token->redirect[j + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(token->redirect[j + 1]);
		if (line->output_fd != -2 && close (line->output_fd) == -1)
			cleanup_close(line, token);
		line->output_fd = fd;
		return (-1);
	}		
	if (line->output_fd != -2 && close (line->output_fd) == -1)
		cleanup_close(line, token);
	line->output_fd = fd;
	return (0);
}

static int	open_output(t_mini *line, t_tokens *token, int j)
{
	int	fd;

	fd = open(token->redirect[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(token->redirect[j + 1]);
		if (line->output_fd != -2 && close (line->output_fd) == -1)
			cleanup_close(line, token);
		line->output_fd = fd;
		return (-1);
	}
	if (line->output_fd != -2 && close (line->output_fd) == -1)
		cleanup_close(line, token);
	line->output_fd = fd;
	return (0);
}

static int	open_input(t_mini *line, t_tokens *token, int j)
{
	int	fd;

	fd = open(token->redirect[j + 1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(token->redirect[j + 1]);
		if (close (line->input_fd) == -1)
			cleanup_close(line, token);
		line->input_fd = fd;
		return (-1);
	}
	if (line->input_fd != -2 && close (line->input_fd) == -1)
		cleanup_close(line, token);
	line->input_fd = fd;
	return (0);
}

int	opening(t_tokens *token, t_mini *line)

{
	int	j;
	int	check;

	j = 0;
	while (token->redirect[j])
	{
		if ((ft_strncmp(token->redirect[j], "<", 2) == 0)
			|| (ft_strncmp(token->redirect[j], "<<", 3) == 0))
			check = open_input(line, token, j);
		else if (ft_strncmp(token->redirect[j], ">", 2) == 0)
			check = open_output(line, token, j);
		else if (ft_strncmp(token->redirect[j], ">>", 3) == 0)
			check = open_output_append(line, token, j);
		if (check == -1)
			return (check);
		j++;
		j++;
	}
	return (0);
}
