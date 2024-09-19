/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2ing_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:18:11 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/10 15:24:56 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup2_in(int *input, int *other, int option)
{
	if (option != 0)
	{
		if (close(*other) == -1)
		{
			ft_putendl_fd("minishell: error while closing a file", 2);
			return (-1);
		}
	}
	if (dup2(*input, STDIN_FILENO) == -1)
	{
		if (close(*input) == -1)
		{
			ft_putendl_fd("minishell: error while closing a file", 2);
			return (-1);
		}
		ft_putendl_fd("dup2_in minishell: dup2 failed", 2);
		return (-1);
	}
	if (close(*input) == -1)
	{
		ft_putendl_fd("minishell: error while closing a file", 2);
		return (-1);
	}
	return (0);
}

int	dup2_out(int *output, int *other, int option)
{
	if (option != 0)
	{
		if (close(*other) == -1)
		{
			ft_putendl_fd("minishell: error while closing a file", 2);
			return (-1);
		}
	}
	if (dup2(*output, STDOUT_FILENO) == -1)
	{
		if (close(*output) == -1)
		{
			ft_putendl_fd("minishell: error while closing a file", 2);
			return (-1);
		}
		ft_putendl_fd("dup2_out minishell: dup2 failed", 2);
		return (-1);
	}
	if (close(*output) == -1)
	{
		ft_putendl_fd("minishell: error while closing a file", 2);
		return (-1);
	}
	return (0);
}
