/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:05:32 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/11 19:10:41 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

static int	no_of_digits(unsigned int n)
{
	int	i;

	i = 1;
	n /= 10;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_utoa(unsigned int n)
{
	char		*str;
	int			digits;
	long int	num;

	num = n;
	digits = no_of_digits(n);
	str = (char *)malloc(sizeof(char) * (digits + 1));
	if (str == NULL)
		return (NULL);
	str[digits] = '\0';
	while ((digits--) > 0)
	{
		str[digits] = num % 10 + '0';
		num = num / 10;
	}
	return (str);
}

int	ft_print_unsigned(unsigned int next_unsigned)
{
	int		count;
	char	*next_int_char;
	char	*ptr;

	count = 0;
	next_int_char = ft_utoa(next_unsigned);
	if (next_int_char == NULL)
		return (-1);
	ptr = next_int_char;
	while (*next_int_char)
	{
		count += ft_print_char(*next_int_char);
		if (count < 0)
		{
			free(ptr);
			return (-1);
		}
		next_int_char++;
	}
	free(ptr);
	return (count);
}
