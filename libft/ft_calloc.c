/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:53:55 by tparratt          #+#    #+#             */
/*   Updated: 2023/11/13 10:39:00 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;

	if (count != 0 && SIZE_MAX / count < size)
		return (NULL);
	res = malloc(count * size);
	if (res == NULL)
		return (NULL);
	ft_bzero(res, count * size);
	return (res);
}
