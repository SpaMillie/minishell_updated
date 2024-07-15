/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:28:28 by tparratt          #+#    #+#             */
/*   Updated: 2024/07/15 14:19:18 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/libft.h"

char	*get_remaining(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (!line)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}

char	*gt_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		line = ft_calloc(i + 2, sizeof(char));
	else
		line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*append_buffer(char *static_buffer, char *read_buffer)
{
	char	*temp;

	temp = ft_strjoin(static_buffer, read_buffer);
	free(static_buffer);
	return (temp);
}

char	*read_file(char *static_buffer, int fd)
{
	char	read_buffer[BUFFER_SIZE + 1];
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		read_buffer[bytes_read] = '\0';
		static_buffer = append_buffer(static_buffer, read_buffer);
		if (!static_buffer)
			return (NULL);
		if (ft_strchr(static_buffer, '\n'))
			break ;
	}
	return (static_buffer);
}

char	*get_next_line(int fd)
{
	static char	*static_buffer;
	char		*line;

	if (fd < 0 || read(fd, NULL, 0) < 0 || BUFFER_SIZE <= 0)
	{
		free(static_buffer);
		static_buffer = NULL;
		return (NULL);
	}
	if (!static_buffer)
		static_buffer = ft_calloc(1, sizeof (char));
	if (!static_buffer)
		return (NULL);
	static_buffer = read_file(static_buffer, fd);
	if (!static_buffer)
		return (NULL);
	line = gt_line(static_buffer);
	if (line)
		static_buffer = get_remaining(static_buffer);
	else if (static_buffer)
	{
		free(static_buffer);
		static_buffer = NULL;
	}
	return (line);
}
