/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:06:43 by tparratt          #+#    #+#             */
/*   Updated: 2024/07/18 19:07:17 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid_identifier_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

static int	is_invalid_start_char(char c)
{
	if (c == '=' || ft_isdigit(c))
		return (1);
	return (0);
}

static char	*handle_error(t_mini *line, char *arg)
{
	line->err_num = 1;
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": not a valid identifier", 2);
	free(arg);
	arg = ft_strdup("");
	if (!arg)
		return (NULL);
	return (arg);
}

static char	*with_valid_start(char *arg, t_mini *line)
{
	int	i;

	i = 0;
	while (arg[i] != '\0' && arg[i] != '=')
	{
		line->err_num = 0;
		if (!is_valid_identifier_char(arg[i]) || arg[i] == '-')
		{
			arg = handle_error(line, arg);
			if (!arg)
				return (NULL);
			break ;
		}
		i++;
	}
	return (arg);
}

char	**export_unset_error_check(char **args, t_mini *line)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (is_invalid_start_char(args[i][0]))
		{
			args[i] = handle_error(line, args[i]);
			if (!args[i])
				return (NULL);
			i++;
			continue ;
		}
		if (ft_strlen(args[i]) != 0)
			args[i] = with_valid_start(args[i], line);
		if (!args[i])
			return (NULL);
		i++;
	}
	return (args);
}
