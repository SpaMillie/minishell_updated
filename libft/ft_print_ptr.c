/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:21:07 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/11 19:07:24 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

static int	ft_format_ptr_hex(unsigned long int next_ptr, int count)
{
	if (next_ptr < 10)
	{
		count += ft_print_char(next_ptr + '0');
		if (count < 0)
			return (-1);
	}
	else
	{
		count += ft_print_char(next_ptr - 10 + 'a');
		if (count < 0)
			return (-1);
	}
	return (count);
}

static int	ft_print_ptr_hex(unsigned long int next_ptr)
{
	int	count;

	count = 0;
	if (next_ptr > 15)
	{
		count += ft_print_ptr_hex(next_ptr / 16);
		if (count < 0)
			return (-1);
		count += ft_print_ptr_hex(next_ptr % 16);
		if (count < 0)
			return (-1);
	}
	else
	{
		count += ft_format_ptr_hex(next_ptr, count);
	}
	return (count);
}

int	ft_print_ptr(unsigned long int next_ptr)
{
	int	count;

	count = 0;
	count += ft_print_char('0');
	if (count < 0)
		return (-1);
	count += ft_print_char('x');
	if (count < 0)
		return (-1);
	count += ft_print_ptr_hex(next_ptr);
	return (count);
}
