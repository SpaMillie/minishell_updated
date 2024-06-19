/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 12:06:43 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/19 12:08:43 by tparratt         ###   ########.fr       */
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

static void	handle_error(t_mini *line, char **args)
{
	line->err_num = 1;
	print_error("not a valid identifier", args);
}

int	export_unset_error_check(char **args, t_mini *line)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		if (is_invalid_start_char(args[i][0]))
		{
			handle_error(line, args);
			return (1);
		}
		j = 0;
		while (args[i][j] != '\0' && args[i][j] != '=')
		{
			if (!is_valid_identifier_char(args[i][j]) || args[i][j] == '-')
			{
				handle_error(line, args);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
