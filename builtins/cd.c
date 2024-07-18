/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:29:33 by tparratt          #+#    #+#             */
/*   Updated: 2024/07/18 11:06:53 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_strings(char *str1, char *str2, char *str3, char *str4)
{
	free(str1);
	free(str2);
	free(str3);
	free(str4);
}

static int	check_args(char **args, t_mini *line, t_tokens *token)
{
	char	*home;

	if (!args[1] || !ft_strncmp(args[1], "~", 2))
	{
		home = get_env_value(line->envp, "HOME", line, token);
		if (chdir(home) == -1)
		{
			line->err_num = 1;
			perror("minishell: cd");
			return (1);
		}
		free(home);
	}
	else
	{
		if (chdir(args[1]) == -1)
		{
			line->err_num = 1;
			perror("minishell: cd");
			return (1);
		}
	}
	return (0);
}

static char	*cd_error_check(char **args, t_mini *line, t_tokens *token)
{
	char	*old_pwd_path;

	if (args[1] && args[2])
	{
		line->err_num = 1;
		print_error("too many arguments", args);
		return (NULL);
	}
	old_pwd_path = getcwd(NULL, 0);
	if (!old_pwd_path)
	{
		perror("getcwd");
		cleanup(line, token, 1);
		exit(1);
	}
	if (check_args(args, line, token) == 1)
	{
		free(old_pwd_path);
		return (NULL);
	}
	else
		return (old_pwd_path);
}

void	cd(char **args, t_mini *line, t_tokens *token)
{
	char	*old_pwd_path;
	char	*new_pwd;
	char	*old_pwd;
	char	*new_pwd_path;

	old_pwd_path = cd_error_check(args, line, token);
	if (!old_pwd_path)
		return ;
	old_pwd = ft_strjoin("OLDPWD=", old_pwd_path);
	if (!old_pwd)
		malloc_failure(line, token);
	new_pwd_path = getcwd(NULL, 0);
	if (!new_pwd_path)
	{
		perror("getcwd");
		cleanup(line, token, 1);
		exit(1);
	}
	new_pwd = ft_strjoin("PWD=", new_pwd_path);
	if (!new_pwd)
		malloc_failure(line, token);
	export(old_pwd, line, token);
	export(new_pwd, line, token);
	free_strings(old_pwd, new_pwd, old_pwd_path, new_pwd_path);
}
