/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:06:44 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/13 14:29:41 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	shell_lvl_check(t_mini *line)
{
	char	*shell_value;
	int		value;
	char	*str;
	char	*str_to_export;

	shell_value = get_env_value(line->envp, "SHLVL", line);
	value = ft_atoi(shell_value);
	value++;
	str = ft_itoa(value);
	str_to_export = ft_strjoin("SHLVL=", str);
	export(str_to_export, line);
}

static void	wait_for_child(t_mini *line)
{
	int	status;

	line->i = 0;
	while (line->i < line->pipe_num)
	{
		if (line->flag == 0)
		{
			wait(&status);
			if (WIFEXITED(status))
				line->err_num = WEXITSTATUS(status);
		}
		line->i++;
	}
}

static void	builtin_execution(t_tokens *token, t_mini *line)
{
	if (line->i == line->pipe_num - 1)
	{
		redirections(&token[line->i]); // Handle redirections for the built-in
		execute_builtin(&token[line->i], line); // Execute the built-in
		line->flag = 1;
	}
	line->i++; // Move to the next command in the pipeline
}

static int	parent(int in_fd, t_mini *line, int *fd)
{
	if (in_fd != STDIN_FILENO)
		close(in_fd);
	if (line->i < line->pipe_num - 1)
	{
		close(fd[1]); // close write end of pipe
		in_fd = fd[0]; // set read end of pipe
	}
	return (in_fd);
}

static int	child(t_tokens *token, t_mini *line, int in_fd, int *fd)
{
	if (!ft_strncmp(token[line->i].command[0], "./minishell", 11))
		shell_lvl_check(line);
	if (in_fd != STDIN_FILENO) // Redirect input
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
			exit(1);
		close(in_fd);
	}
	if (line->i < line->pipe_num - 1) // Redirect output
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit(1);
		close(fd[1]);
	}
	redirections(&token[line->i]);
	/* if (is_builtin(&token[line->i]))
	{
		builtin_execution(token, line); // Execute the built-in
		exit(line->err_num);
	} */
	//else
	//{
	if (execve(get_path(token[line->i].command, line->envp), token[line->i].command, line->envp) == -1)
		exit(1);
	//}
	return (in_fd);
}

void	execute(t_tokens *token, t_mini *line)
{
	int		fd[2];
	pid_t	pid;
	int		in_fd;

	in_fd = STDIN_FILENO;
	line->i = 0;
	while (line->i < line->pipe_num)
	{
		line->flag = 0;
		if (line->i < line->pipe_num - 1 && pipe(fd) == -1)
			exit(1);
		if (is_builtin(&token[line->i]))
		{
			builtin_execution(token, line); // Execute the built-in
			continue ;
		}
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
		{
			if (!is_builtin(&token[line->i]))
				in_fd = child(token, line, in_fd, fd);
		}
		else
			in_fd = parent(in_fd, line, fd);
		line->i++;
	}
	wait_for_child(line);
}
