/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:57:43 by tparratt          #+#    #+#             */
/*   Updated: 2024/02/20 17:20:06 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_format_hex(unsigned int next_hex, const char format, int count)
{
	if (next_hex < 10)
	{
		count += ft_print_char(next_hex + '0');
		if (count < 0)
			return (-1);
	}
	else
	{
		if (format == 'x')
		{
			count += ft_print_char(next_hex - 10 + 'a');
			if (count < 0)
				return (-1);
		}
		else if (format == 'X')
		{
			count += ft_print_char(next_hex - 10 + 'A');
			if (count < 0)
				return (-1);
		}
	}
	return (count);
}

int	ft_print_hex(unsigned int next_hex, const char format)
{
	int	count;

	count = 0;
	if (next_hex > 15)
	{
		count += ft_print_hex(next_hex / 16, format);
		if (count < 0)
			return (-1);
		count += ft_print_hex(next_hex % 16, format);
		if (count < 0)
			return (-1);
	}
	else
	{
		count += ft_format_hex(next_hex, format, count);
	}
	return (count);
}
