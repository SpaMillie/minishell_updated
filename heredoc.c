/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:22:45 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/17 14:46:00 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (ft_strlen(s2) == 0)
	{
		if (ft_strlen(s1) - 1 == 0)
			return (0);
		else
			return (1);
	}
	while (s1[i] == s2[i] && s1[i + 1] != '\0' && s2[i] != '\0' && i < n)
		i++;
	if (s1[i + 1] == '\0' && s2[i] == '\0')
		return (0);
	else
		return (1);
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

static char	*hdoc_loop(char *hdoc_line, int fd, char *delim)
{
	while (hdoc_line)
	{
		if (!heredoc_strncmp(hdoc_line, delim, ft_strlen(delim)))
			break ;
		write(1, "heredoc> ", 9);
		ft_putstr_fd(hdoc_line, fd);
		free(hdoc_line);
		hdoc_line = get_next_line(0);
	}
	return (hdoc_line);
}

static char	*null_hdoc_line(char *hdoc_line, char *delim, t_mini *line)
{
	char	*str;

	if (!hdoc_line)
	{
		write(1, "\n", 1);
		free(delim);
		free(hdoc_line);
		signal(SIGINT, handle_ctrl_c);
		str = ft_strdup("");
		if (!str)
			malloc_failure_without_token(line);
		return (str);
	}
	return (NULL);
}

static char	*hdocing(char *delim, char *hd, t_mini *line)
{
	int				fd;
	char			*hdoc_line;
	char			*str;

	signal(SIGINT, handle_heredoc_sig);
	fd = open(hd, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd == -1)
		return (NULL);
	write(1, "heredoc> ", 9);
	hdoc_line = get_next_line(0);
	hdoc_line = hdoc_loop(hdoc_line, fd, delim);
	str = null_hdoc_line(hdoc_line, delim, line);
	if (str)
		return (str);
	if (close(fd) == -1)
		return (NULL);
	free(delim);
	free(hdoc_line);
	return (hd);
}

static char	*create_hd_name(int hd_num, t_mini *line)
{
	char	*str;

	str = here_strjoin(".here_", simple_itoa(hd_num));
	if (!str)
		malloc_failure_without_token(line);
	return (str);
}

static void	free_before_return(t_mini *line, char *hd_name)
{
	free_2d(line->element);
	free_2d(line->metaed);
	free(hd_name);
}

static void	free_and_exit(t_mini *line, char *hd_name)
{
	ft_putendl_fd("minishell: couldn't handle here_doc", 2);
	free_2d(line->element);
	free_2d(line->metaed);
	free(hd_name);
	free_2d(line->envp);
	exit(1);
}

int	here_doc(t_mini *line)
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
			hd_name = create_hd_name(hd_num, line);
			line->metaed[i + 1] = hdocing(line->metaed[i + 1], hd_name, line);
			if (line->metaed[i + 1] == NULL)
				free_and_exit(line, hd_name);
			if (ft_strlen(line->metaed[i + 1]) == 0)
			{
				free_before_return(line, hd_name);
				return (1);
			}
			hd_num++;
		}
		i++;
	}
	return (0);
}
