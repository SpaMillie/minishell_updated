/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:06:29 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/17 15:43:58 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*simple_itoa(int n)
{
	int		len;
	char	*str;

	len = ft_intlen(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	while (n)
	{
		str[len--] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

void	free_before_return(t_mini *line, char *hd_name, int hd_num)
{
	int	i;

	i = 1;
	unlink(hd_name);
	free(hd_name);
	while (i < hd_num)
	{
		hd_name = create_hd_name(hd_num - i, line);
		unlink(hd_name);
		free(hd_name);
		i++;
	}
	free_2d(line->element);
	free_2d(line->metaed);
}
