/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 15:03:15 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/17 15:07:20 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_strncmp(const char *s1, const char *s2, size_t n)
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

int	ft_intlen(int n)
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

char	*hdoc_loop(char *hdoc_line, int fd, char *delim)
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

char	*null_hdoc_line(char *hdoc_line, char *delim, t_mini *line)
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
