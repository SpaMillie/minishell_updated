/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:14:26 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/10 18:21:00 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_fds	first_child(t_mini *line, t_tokens *token, int *fd)
{		
	t_fds	cur;

	cur.close = fd[0];
	if (!has_input(token))
		cur.in = -2;
	else
		cur.in = line->input_fd;
	if (!has_output(token))
		cur.out = fd[1];
	else
	{
		if (close (fd[1]) == -1)
			cleanup_close(line, token);
		cur.out = line->output_fd;
	}
	return (cur);
}

static t_fds	middle_child(t_mini *line, t_tokens *token,
	int *fd, int *prev_read)
{
	t_fds	cur;

	cur.close = fd[0];
	if (!has_input(token))
		cur.in = *prev_read;
	else
	{
		if (close (*prev_read) == -1)
			cleanup_close(line, token);
		cur.in = line->input_fd;
	}	
	if (!has_output(token))
		cur.out = fd[1];
	else
	{
		if (close (fd[1]) == -1)
			cleanup_close(line, token);
		cur.out = line->output_fd;
	}	
	return (cur);
}

static t_fds	last_child(t_mini *line, t_tokens *token, int *prev_read)
{
	t_fds	cur;

	cur.close = -2;
	if (!has_input(token))
		cur.in = *prev_read;
	else
	{
		if (close (*prev_read) == -1)
			cleanup_close(line, token);
		cur.in = line->input_fd;
	}
	if (!has_output(token))
		cur.out = -2;
	else
		cur.out = line->output_fd;
	return (cur);
}

static t_fds	only_child(t_mini *line, t_tokens *token)
{
	t_fds	cur;

	cur.close = -2;
	if (!has_input(token))
		cur.in = -2;
	else
		cur.in = line->input_fd;
	if (!has_output(token))
		cur.out = -2;
	else
		cur.out = line->output_fd;
	return (cur);
}

t_fds	set_fds(t_mini *line, t_tokens *token, int *prev)
{
	t_fds	cur;
	int		fd[2];

	if (line->i == 0 && line->pipe_num == 1)
		cur = only_child(line, token);
	else
	{
		if (line->i < line->pipe_num - 1)
		{
			if (pipe(fd) == -1)
			{
				ft_putendl_fd("minishell: pipe failed", 2);
				cleanup(line, token, 1);
				exit (1);
			}
		}
		if (line->i == 0)
			cur = first_child(line, token, fd);
		else if (line->i == line->pipe_num - 1)
			cur = last_child(line, token, prev);
		else
			cur = middle_child(line, token, fd, prev);
	}
	return (cur);
}
