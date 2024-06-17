/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:48:57 by mspasic           #+#    #+#             */
/*   Updated: 2024/06/05 15:33:18 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//most printf's should be exits

// typedef struct s_tokens
// {
//     char    **cmnd;
//     char    **redirect;
// }   t_tokens;

// typedef struct s_mini
// {
//     char        **metaed;
//      char    **element; //this needs to be added
//     int         pipe_num;
// }   t_mini;

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
    int len;

    len = ft_strlen(s);
    if (ft_strncmp(s, "<", len) == 0 || ft_strncmp(s, ">", len) == 0 || \
        ft_strncmp(s, ">>", len) == 0 || ft_strncmp(s, "<<", len) == 0)
        return (0);
    return (-1);
}

void    validating(char *argv, t_mini *line)
{
	int	words;
	int	i;

    i = 0;
	if (first_split(argv, line) == -1)
		printf("zsh: could not find the matching quote\n");
	// i = 0;
    // while (line->element[i] != NULL)
    //     printf("%s\n", line->element[i++]);
	words = second_split(line);
	// i = 0;
    // while (line->metaed[i] != NULL)
    //     printf("%s\n", line->metaed[i++]);
    if (ft_strlen(line->metaed[i]) != 0 && ft_strncmp(line->metaed[i], "|", ft_strlen(line->metaed[i])) == 0)
        printf("zsh: parse error near `|'\n");
    while (i + 1 < words)
    {
        if (ft_strlen(line->metaed[i]) != 0 && is_it_redirect(line->metaed[i]) == 0 && is_it_redirect(line->metaed[i + 1]) == 0)
           printf("zsh: parse error near i + 1\n"); //needs a function to output the second redirection
        i++;
    }
    if (ft_strlen(line->metaed[i]) != 0 && (ft_strncmp(line->metaed[i], "|", ft_strlen(line->metaed[i])) == 0 || \
        (is_it_redirect(line->metaed[i]) == 0)))
        printf("zsh: parse error near \\n\n");
    trim_quotes(line);
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
