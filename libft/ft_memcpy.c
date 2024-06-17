/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:14:45 by tparratt          #+#    #+#             */
/*   Updated: 2023/11/08 10:52:00 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*source;
	char	*dest;

	if (dst == NULL && src == NULL)
		return (NULL);
	source = (char *)src;
	dest = (char *)dst;
	i = 0;
	while (i < n)
	{
		dest[i] = source[i];
		i++;
	}
	return (dest);
}
