/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:22:45 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/17 15:42:27 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_hd_name(int hd_num, t_mini *line)
{
	char	*str;

	str = here_strjoin(".here_", simple_itoa(hd_num));
	if (!str)
		malloc_failure_without_token(line);
	return (str);
}

static void	free_and_exit(t_mini *line, int hd_num, char *hd_name)
{
	int	i;

	i = 1;
	unlink(hd_name);
	free(hd_name);
	while (i < hd_num)
	{
		hd_name = create_hd_name(hd_num - i, line);
		unlink(hd_name);
		free(hd_name);
		i++;
	}
	ft_putendl_fd("minishell: couldn't handle here_doc", 2);
	free_2d(line->element);
	free_2d(line->metaed);
	free_2d(line->envp);
	exit(1);
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
				free_and_exit(line, hd_num, hd_name);
			if (ft_strlen(line->metaed[i + 1]) == 0)
			{
				free_before_return(line, hd_name, hd_num);
				return (1);
			}
			hd_num++;
		}
		i++;
	}
	return (0);
}
