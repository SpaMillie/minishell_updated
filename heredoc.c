/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:22:45 by mspasic           #+#    #+#             */
/*   Updated: 2024/06/11 13:18:44 by tparratt         ###   ########.fr       */
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
		printf("malloc fail\n");
	str[len--] = '\0';
	while (n)
	{
		str[len--] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

static char    *heredocing(char *delim, char *hd)
{
    int     fd;
    int     check;
	char	*line;

    check = 0;
    fd = open(hd, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd == -1)
		printf("error while opening file\n");
	line = readline("heredoc> ");
	ft_putendl_fd(line, fd); // Tom added this
	while (ft_strncmp(delim, line, ft_strlen(delim)) != 0)
	{
		free (line);
		line = readline("heredoc> ");
		if (line == NULL)
			break ;
		if (ft_strncmp(delim, line, ft_strlen(delim)) != 0) // Tom added this
			ft_putendl_fd(line, fd); // Tom changed this
	}
    check = close(fd);
    if (check == -1)
        printf("error while closing file\n");
    free (delim);
	free (line);
	line = ft_strdup("");
	free (line);
    return (hd); //unlink heredocs in cleanup and close fds
}

void    here_doc(t_mini *line)
{
    int 	hd_num;
	int		i;
	char 	*hd_name;

    hd_num = 1;
	i = 0;
    while (line->metaed[i] != NULL)
    {
        if (ft_strncmp(line->metaed[i], "<<", 3) == 0) // Tom changed this
        {
			hd_name = here_strjoin(".here_", simple_itoa(hd_num));
			//line->metaed[i + 1] can't be NULL and it can't be a meta which was checked before in validation (syntax errors) so no check is neccessary
            line->metaed[i + 1] = heredocing(line->metaed[i + 1], hd_name);
            hd_num++;
        }
        i++;
    }
}
