/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 11:58:47 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/03 10:55:13 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl_c(int signal)
{
	if (signal != SIGINT)
		return ;
	if (signal == SIGINT)
	{
		g_sigflag = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_term_attr(struct termios *tios)
{
	tios->c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, tios);
}

void	set_term_attr_hdoc(struct termios *tios)
{
	tios->c_cc[VQUIT] = _POSIX_VDISABLE;
	tios->c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, tios);
}

void	reset_term_attr(struct termios *tios)
{
	tios->c_lflag |= (ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, tios);
}

void	reset_term_attr_hdoc(struct termios *tios)
{
	tios->c_cc[VQUIT] = 034;
	tios->c_lflag |= (ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, tios);
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
	if (signal != SIGINT)
		return ;
	if (signal == SIGINT)
		g_sigflag = 130;
}

void	handle_heredoc_sig(int signal)
{
	char	eot;

	eot = 4;
	if (signal != SIGINT)
		return ;
	if (signal == SIGINT)
	{
		g_sigflag = 1;
		printf("\n");
		ioctl(STDIN_FILENO, TIOCSTI, &eot);
	}
}
