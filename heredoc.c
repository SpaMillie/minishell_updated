/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:22:45 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/10 18:37:41 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*here_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s2);
	return (str);
}

static int	ft_intlen(int n)
{
	int	i;

	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*simple_itoa(int n)
{
	int		len;
	char	*str;

	len = ft_intlen(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	while (n)
	{
		str[len--] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

static char	*heredocing(char *delim, char *hd)
{
	int		fd;
	char	*line;

	fd = open(hd, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd == -1)
		return (NULL);
	line = readline("heredoc> ");
	ft_putendl_fd(line, fd);
	while (ft_strncmp(delim, line, ft_strlen(delim)) != 0)
	{
		free (line);
		line = readline("heredoc> ");
		if (line == NULL)
			break ;
		if (ft_strncmp(delim, line, ft_strlen(delim)) != 0)
			ft_putendl_fd(line, fd);
	}
	if (close (fd) == -1)
		return (NULL);
	free (delim);
	free (line);
	return (hd);
}

void	here_doc(t_mini *line)
{
	int		hd_num;
	int		i;
	char	*hd_name;

	hd_num = 1;
	i = 0;
	while (line->metaed[i] != NULL)
	{
		if (ft_strncmp(line->metaed[i], "<<", 3) == 0)
		{
			hd_name = here_strjoin(".here_", simple_itoa(hd_num));
			if (!hd_name)
				malloc_failure_without_token(line);
			line->metaed[i + 1] = heredocing(line->metaed[i + 1], hd_name);
			if (line->metaed[i + 1] == NULL)
			{
				ft_putendl_fd("minishell: couldn't handle here_doc", 2);
				free_2d(line->metaed);
				free_2d(line->envp);
				exit (1);
			}
			hd_num++;
		}
		i++;
	}
}
