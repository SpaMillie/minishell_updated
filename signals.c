/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:58:47 by tparratt          #+#    #+#             */
/*   Updated: 2024/07/16 14:50:37 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		g_sigflag = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	check_g_sigflag(t_mini *line)
{
	if (g_sigflag)
	{
		line->err_num = g_sigflag;
		g_sigflag = 0;
	}
}

void	handle_sigint(int signal)
{
	if (signal == SIGINT)
		g_sigflag = 130;
}

void	handle_sigquit(int signal)
{
	char	eot;

	eot = 3;
	ft_putendl_fd("Quit (core dumped)", 1);
	if (signal == SIGQUIT)
	{
		g_sigflag = 131;
		ioctl(STDIN_FILENO, TIOCSTI, &eot);
	}
}

void	handle_heredoc_sig(int signal)
{
	char	eot;

	eot = 4;
	if (signal == SIGINT)
	{
		g_sigflag = 1;
		ioctl(STDIN_FILENO, TIOCSTI, &eot);
	}
}
