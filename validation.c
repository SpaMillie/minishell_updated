/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:48:57 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/16 17:57:57 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_it_space(char *s, int i)
{
	if ((s[i] == 32 || (s[i] < 14 && s[i] > 8)))
		return (0);
	return (1);
}

int ft_skip(char *s, int i)
{
    char    c;

    c = s[i];
    i++;
    while (s[i] != '\0' && s[i] != c)
        i++;
    if (s[i] == c)
        return (i + 1);
    else
        return (-1);
}

int is_it_redirect(char *s)
{
    if (ft_strncmp(s, "<", 2) == 0 || ft_strncmp(s, ">", 2) == 0 || \
        ft_strncmp(s, ">>", 3) == 0 || ft_strncmp(s, "<<", 3) == 0)
        return (0);
    return (-1);
}

int validating(char *argv, t_mini *line, char *line_read)
{
	int	words;
	int	i;

    i = 0;
	if (first_split(argv, line) == -1)
		return (syntax_error(line, NULL, 1));
    words = second_split(line);
    if (line->metaed[i] == NULL)
        return (empty_command(line, line_read));
    if (ft_strncmp(line->metaed[i], "\"\"", 3) != 0 && ft_strncmp(line->metaed[i], "''", 3) != 0 && ft_strlen(line->metaed[i]) != 0 && ft_strncmp(line->metaed[i], "|", ft_strlen(line->metaed[i])) == 0)
		return (syntax_error(line, NULL, 2));
    while (i + 1 < words)
    {
        if (ft_strncmp(line->metaed[i], "\"\"", 3) != 0 && ft_strncmp(line->metaed[i], "''", 3) != 0 && ft_strlen(line->metaed[i]) != 0 && is_it_redirect(line->metaed[i]) == 0 && is_it_redirect(line->metaed[i + 1]) == 0)
		    return (syntax_error(line, line->metaed[i + 1], 3));
        i++;
    }
    if (ft_strncmp(line->metaed[i], "\"\"", 3) != 0 && ft_strncmp(line->metaed[i], "''", 3) != 0 && ft_strlen(line->metaed[i]) != 0 && (ft_strncmp(line->metaed[i], "|", ft_strlen(line->metaed[i])) == 0 || \
        (is_it_redirect(line->metaed[i]) == 0)))
		return (syntax_error(line, NULL, 4));
    trim_quotes(line);
    here_doc(line);
    return (0);
}

// int main(void)
// {
//     t_mini  line;
//     // the actual line_read will replace the line_read
//     char line_read[] = "ech'o ' '$hey'>>$home|ed";

//     line = (t_mini){0};
//     validating(line_read, &line);
// 	
//     // for checking the arguments, ie, will be deleted after
//     // int i = 0;
//     // while (line.metaed[i] != NULL)
//     //     printf("%s\n", line.metaed[i++]);
// 	// function (&line);
// 	free_double(line.element);
// 	free_double(line.metaed);
// }
