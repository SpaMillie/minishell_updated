#include "minishell.h"

void	second_splitting(t_mini *line)
{
	int	prev_j;
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (line->element[i] != NULL)
	{
		j = 0;
		while (line->element[i][j] != '\0')
		{
			prev_j = j;
			if (line->element[i][j] == '>' || line->element[i][j] == '<' || line->element[i][j] == '|')
			{
				if ((line->element[i][j] == '>' && line->element[i][j + 1] == '>') || (line->element[i][j] == '<' &&  line->element[i][j + 1] == '<'))
					j++;
				j++;
			}
			else
			{
				while (line->element[i][j] != '\0' && line->element[i][j] != '>' && line->element[i][j] != '<' && line->element[i][j] != '|')
				{
					if (line->element[i][j] == '\'' || line->element[i][j] == '\"')
						j = ft_skip(line->element[i], j);
					else
						j++;
				}
			}
			line->metaed[k++] = ft_substr(line->element[i], prev_j, j - prev_j);
		    if (line->metaed[k - 1] == NULL)
				malloc_failure(line);
		}
		i++;	
	}
	line->metaed[k] = NULL;
}

static int	w_count(t_mini *line)
{
	int	i;
	int	j;
	int	words;

	i = 0;
	words = 0;
	while (line->element[i] != NULL)
	{
		j = 0;
		while (line->element[i][j] != '\0')
		{
			if (line->element[i][j] == '>' || line->element[i][j] == '<' || line->element[i][j] == '|')
			{
				if ((line->element[i][j] == '>' && line->element[i][j + 1] == '>') || (line->element[i][j] == '<' &&  line->element[i][j + 1] == '<'))
					j++;
				j++;
				words++;
			}
			else
			{
				while (line->element[i][j] != '\0' && line->element[i][j] != '>' && line->element[i][j] != '<' && line->element[i][j] != '|')
				{
					if (line->element[i][j] == '\'' || line->element[i][j] == '\"')
						j = ft_skip(line->element[i], j);
					else
						j++;
				}
				words++;
			}
		}
		i++;
	}
	return (words);
}

int	second_split(t_mini *line)
{
	int	words;

	words = w_count(line);
	// printf("words are %d\n", words);
	line->metaed = (char **)malloc(sizeof(char *) * (words + 1));
	if (!line->metaed)
		malloc_failure(line);
	second_splitting(line);
	return (words);
}
