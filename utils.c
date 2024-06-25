/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 14:00:48 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/25 11:35:34 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *message, char **args)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(message, 2);
}

char	**malloc_2d(char **arr)
{
	char	**new_arr;
	int		i;

	i = 0;
	while (arr[i])
		i++;
	new_arr = malloc(sizeof(char *) * (i + 2));
	if (!new_arr)
		return (NULL);
	return (new_arr);
}

char	**envp_dup(char **envp)
{
	char	**res;
	int		i;

	res = malloc_2d(envp);
	if (!res)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		res[i] = ft_strdup(envp[i]);
		if (!res[i])
			return (NULL);
		i++;
	}
	res[i] = NULL;
	return (res);
}

char	*build_prompt(char *username, char *hostname, char *cwd)
{
	char	*prompt;

	prompt = ft_strdup(username);
	if (!prompt)
		malloc_failure_no_cleanup();
	prompt = join_and_free(prompt, "@");
	if (!prompt)
		malloc_failure_no_cleanup();
	prompt = join_and_free(prompt, hostname);
	if (!prompt)
		malloc_failure_no_cleanup();
	prompt = join_and_free(prompt, ":");
	if (!prompt)
		malloc_failure_no_cleanup();
	prompt = join_and_free(prompt, cwd);
	if (!prompt)
		malloc_failure_no_cleanup();
	free(cwd);
	prompt = join_and_free(prompt, "$ ");
	if (!prompt)
		malloc_failure_no_cleanup();
	return (prompt);
}	
