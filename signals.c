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

void	set_term_attr(void)
{
	struct termios	term_attr;

	tcgetattr(STDIN_FILENO, &term_attr);
	term_attr.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term_attr);
}

//Ctrl+C sends SIGINT. Ctrl+\ sends SIGQUIT
void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}
