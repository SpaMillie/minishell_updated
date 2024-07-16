/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:22:45 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/16 14:03:53 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_strncmp(const char *s1, const char *s2)
{
	size_t	i;

	printf("s1 is %s, s2 is %s\n", s1, s2);
	i = 1;
	if (ft_strlen(s2) == 0)
	{
		if (ft_strlen(s1) - 1 == 0)
			return (0);
		else
			return ((unsigned char)*s1 - (unsigned char)*s2);
	}
	while (*s1 == *s2 && *s1 + 1 != '\0' && *s2 != '\0')
	{
		s1++;
		s2++;
		i++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

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
	int				fd;
	char			*line;

	signal(SIGINT, handle_heredoc_sig);
	fd = open(hd, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd == -1)
		return (NULL);
	write(1, "heredoc> ", 9);
	line = get_next_line(0);
	printf("line is %s\n", line);
	while (line)
	{
		if (!heredoc_strncmp(line, delim))
			break ;
		write(1, "heredoc> ", 9);
		ft_putstr_fd(line, fd);
		free(line);
		line = get_next_line(0);
	}
	if (close (fd) == -1)
		return (NULL);
	write(1, "\n", 1);
	free (delim);
	free (line);
	signal(SIGINT, handle_ctrl_c);
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
