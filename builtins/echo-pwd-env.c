/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo-pwd-env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:16:35 by tparratt          #+#    #+#             */
/*   Updated: 2024/07/11 13:38:09 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	all_ens(char *arg)
{
	int	i;

	i = 1;
	if (ft_strlen(arg) == 1 || ft_strlen(arg) == 0)
		return (0);
	while(arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	echon(char **args)
{
	int	i;

	i = 2;
	while (args[i])
	{
		if (all_ens(args[i]))
			i++;
		if (args[i + 1] == NULL)
			ft_printf("%s", args[i]);
		else
			ft_printf("%s ", args[i]);
		i++;
	}
}

void	echo(char **args)
{
	int	i;

	if (!args[1])
		ft_printf("\n");
	else
	{
		if (all_ens(args[1]))
			echon(args);
		else
		{
			i = 1;
			while (args[i])
			{
				if (args[i + 1] == NULL || ft_strlen(args[i]) == 0)
					ft_printf("%s", args[i]);
				else
					ft_printf("%s ", args[i]);
				i++;
			}
			ft_printf("\n");
		}
	}
}

void	pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		exit(1);
	ft_printf("%s\n", cwd);
	free(cwd);
}

void	env(char **args, t_mini *line)
{
	int	i;

	if (args[1])
	{
		line->err_num = 1;
		print_error("too many arguments", args);
	}
	else
	{
		i = 0;
		while (line->envp[i])
		{
			if (ft_strchr(line->envp[i], '='))
				ft_printf("%s\n", line->envp[i]);
			i++;
		}
	}
}
