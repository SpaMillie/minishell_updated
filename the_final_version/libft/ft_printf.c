/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 13:33:40 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/11 19:07:24 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

static int	ft_format(const char format, int count, va_list args)
{
	if (format == 'c')
		count = ft_print_char(va_arg(args, int));
	else if (format == 's')
		count = ft_print_str(va_arg(args, char *));
	else if (format == 'd' || format == 'i')
		count = ft_print_int(va_arg(args, int));
	else if (format == 'u')
		count = ft_print_unsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		count = ft_print_hex(va_arg(args, unsigned int), format);
	else if (format == 'p')
		count = ft_print_ptr((unsigned long int)va_arg(args, void *));
	else if (format == '%')
		count = ft_print_char(format);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		ret;

	va_start(args, format);
	count = 0;
	ret = 0;
	while (*format)
	{
		if (*format != '%')
			count = ft_print_char(*format);
		else
			count = ft_format(*++format, count, args);
		if (count < 0)
			return (-1);
		ret += count;
		format++;
	}
	va_end(args);
	return (ret);
}
