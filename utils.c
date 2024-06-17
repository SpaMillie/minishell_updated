/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:00:48 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/12 15:12:15 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *message, char **args)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": ", 2);
	if (!args[2])
	{
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(message, 2);
}

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

void	malloc_failure(void)
{
	ft_putendl_fd("minishell: malloc failure", 2);
	exit(1);
}

char	**malloc_2d(char **arr)
{
	char	**new_arr;
	int		i;

	i = 0;
	while (arr[i])
		i++;
	new_arr = malloc(sizeof(char *) * (i + 2));
	if (!new_arr)
		return (NULL);
	return (new_arr);
}

char	**envp_dup(char **envp)
{
	char	**res;
	int		i;

	res = malloc_2d(envp);
	if (!res)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		res[i] = ft_strdup(envp[i]);
		if (!res[i])
			return (NULL);
		i++;
	}
	res[i] = NULL;
	return (res);
}
