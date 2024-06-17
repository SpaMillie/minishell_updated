/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:05:02 by tparratt          #+#    #+#             */
/*   Updated: 2023/11/08 11:59:48 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str1;
	char	*str2;
	char	*str;
	int		i;
	int		j;

	str1 = (char *)s1;
	str2 = (char *)s2;
	str = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	while (str1[i] != '\0')
	{
		str[i] = str1[i];
		i++;
	}
	while (str2[j] != '\0')
		str[i++] = str2[j++];
	str[i] = '\0';
	return (str);
}
