/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo-pwd-env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:16:35 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/12 14:44:11 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	echon(char **args)
{
	int	i;

	i = 2;
	while (args[i])
	{
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
		if (!ft_strncmp(args[1], "-n", 3))
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
