/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:28:58 by tparratt          #+#    #+#             */
/*   Updated: 2024/07/18 18:52:31 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_existing_name(char *existing, t_mini *line, int i)
{
	int	j;

	j = 0;
	while (line->envp[i][j] != '=' && line->envp[i][j] != '\0')
	{
		existing[j] = line->envp[i][j];
		j++;
	}
	existing[j] = '\0';
	return (existing);
}

static char	*env_exists(char *arg, t_mini *line, t_tokens *token)
{
	int		len;
	int		i;
	char	*existing;

	len = 0;
	if (ft_strlen(arg) != 0)
		return (NULL);
	while (arg[len] != '=' && arg[len] != '\0')
		len++;
	i = 0;
	while (line->envp[i])
	{
		if (!ft_strncmp(line->envp[i], arg, len))
		{
			existing = malloc(sizeof(char) * len + 1);
			if (!existing)
				malloc_failure(line, token);
			existing = get_existing_name(existing, line, i);
			return (existing);
		}
		i++;
	}
	return (NULL);
}

static void	unset_existing(char *arg, t_mini *line, t_tokens *token)
{
	char		*existing;

	existing = env_exists(arg, line, token);
	if (existing)
	{
		unset(existing, line, token);
		free(existing);
	}
}

void	export(char *arg, t_mini *line, t_tokens *token)
{
	char	**new_envp;
	int		i;

	unset_existing(arg, line, token);
	new_envp = malloc_2d(line->envp);
	if (!new_envp)
		malloc_failure(line, token);
	i = 0;
	while (line->envp[i])
	{
		new_envp[i] = ft_strdup(line->envp[i]);
		if (!new_envp[i])
			malloc_failure(line, token);
		i++;
	}
	new_envp[i] = ft_strdup(arg);
	if (!new_envp[i])
		malloc_failure(line, token);
	i++;
	new_envp[i] = NULL;
	free_2d(line->envp);
	line->envp = new_envp;
}

void	export_cmd(char **args, t_mini *line, t_tokens *token)
{
	int	i;

	if (!args[1])
	{
		i = 0;
		while (line->envp[i])
		{
			ft_printf("declare -x %s\n", line->envp[i]);
			i++;
		}
	}
	else
	{
		token[line->i].command = export_unset_error_check(args, line);
		if (!token[line->i].command)
			malloc_failure(line, token);
		i = 1;
		while (args[i])
		{
			if (ft_strlen(args[i]) != 0)
				export(args[i], line, token);
			i++;
		}
	}
}
