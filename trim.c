#include "minishell.h"

static char	*trim_copy(t_mini *line, char *copy, int i, int j)
{
	int		k;
	char	c;

	k = 0;
	c = line->metaed[i][j];
	while (k < j)
	{
		copy[k] = line->metaed[i][k];
		k++;
	}
	j++;
	while (line->metaed[i][j] != c)
	{
		if (c == '\'' && line->metaed[i][j] == '$')
		{
			copy[k++] = 7;
			j++;
		}
		else
			copy[k++] = line->metaed[i][j++];
	}
	j++;
	while (line->metaed[i][j] != '\0')
		copy[k++] = line->metaed[i][j++];
	copy[k] = '\0';
	free(line->metaed[i]);
	return (copy);
}

static int	snip_snip(t_mini *line, int i, int j)
{
	char	*trimmed_string;
	int		len;
	char	c;
	int		count;

	len = ft_strlen(line->metaed[i]);
	c = line->metaed[i][j];
	count = j + 1;
	trimmed_string = malloc((sizeof(char)) * (len - 1));
	if (!trimmed_string)
		printf("malloc error\n");
	while (line->metaed[i][count] != c)
		count++;
	count = count - 1;
	// printf("count is %d\n", count);
	line->metaed[i] = trim_copy(line, trimmed_string, i, j);
	return (count);
}

void	trim_quotes(t_mini *line)
{
	int	i;
	int	j;

	i = 0;
	while (line->metaed[i] != NULL)
	{
		j = 0;
		while (line->metaed[i][j] != '\0')
		{
			if (line->metaed[i][j] == '\'' || line->metaed[i][j] == '\"') 
				j = snip_snip(line, i, j);
			else
				j++;
		}
		// printf("new metaed is %s\n", line->metaed[i]);
		i++;
	}
}

