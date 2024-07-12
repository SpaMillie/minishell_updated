/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:57:05 by tparratt          #+#    #+#             */
/*   Updated: 2024/07/12 13:35:39 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

int	ft_print_str(char *next_str)
{
	int		count;

	count = 0;
	if (next_str == NULL)
	{
		count += write(1, "(null)", 6);
		if (count < 0)
			return (-1);
	}
	else if (ft_strlen(next_str) == 0)
		return (0);
	else
	{
		while (*next_str)
		{
			count += write(1, &(*next_str), 1);
			if (count < 0)
				return (-1);
			next_str++;
		}
	}
	return (count);
}
