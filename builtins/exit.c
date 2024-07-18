/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:43:38 by tparratt          #+#    #+#             */
/*   Updated: 2024/07/18 14:19:30 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	non_numeric_arg(char **args, t_mini *line, t_tokens *token)
{
	int	i;
	int	num;

	i = 0;
	if (line->pipe_num == 1)
		ft_printf("exit\n");
	line->err_num = 2;
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]) && args[1][i] != '+' && args[1][i] != '-')
		{
			print_error("numeric argument required", args);
			if (line->pipe_num == 1)
			{
				cleanup(line, token, 1);
				exit(2);
			}
			return ;
		}
		i++;
	}
	num = ft_atoi(args[1]);
	if (line->i == line->pipe_num)
		cleanup(line, token, 1);
	exit(num);
}

void	exit_cmd(char **args, t_mini *line, t_tokens *token)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		line->err_num = 1;
		print_error("too many arguments", args);
		return ;
	}
	else if (i > 1)
		non_numeric_arg(args, line, token);
	else if (i == 1)
	{
		if (line->pipe_num == 1)
		{
			ft_printf("exit\n");
			cleanup(line, token, 1);
			exit(0);
		}
		if (line->i == line->pipe_num)
			cleanup(line, token, 1);
		exit(0);
	}
}
