/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:15:28 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/18 21:16:34 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_fd(int *input, int *output)
{		
	*input = dup(STDIN_FILENO);
	if (*input == -1)
	{
		ft_putendl_fd("minishell: dup failed", 2);
		return (-1);
	}
	*output = dup(STDOUT_FILENO);
	if (*output == -1)
	{
		ft_putendl_fd("minishell: dup failed", 2);
		return (-1);
	}
	return (0);
}

int	close_cleanup(t_mini *line)
{
	if (line->input_fd != -2 && line->input_fd != -1)
	{
		close(line->input_fd);
		line->input_fd = -2;
	}
	if (line->output_fd != -2 && line->output_fd != -1)
	{
		close(line->output_fd);
		line->output_fd = -2;
	}
	return (0);
}
