/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:56:00 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/11 19:07:24 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

int	ft_print_int(int next_int)
{
	int		count;
	char	*next_int_char;
	char	*ptr;

	count = 0;
	next_int_char = ft_itoa(next_int);
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
