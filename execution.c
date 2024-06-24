/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: milica <milica@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:06:44 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/24 16:16:47 by milica           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!ft_strncmp(token[line->i].command[0], "./minishell", 12)) //what if token[line->i].command[0] == ./minishellsoemthing?
		shell_lvl_check(line);
	if (in_fd != STDIN_FILENO) // Redirect input
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
		{
			ft_putstr_fd("minishell: dup2 failed", 2);
			close(in_fd);
			return (-1);
		}
		close(in_fd);
	}
	if (line->i < line->pipe_num - 1) // Redirect output
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			ft_putstr_fd("minishell: dup2 failed", 2);
			close(in_fd);
			return (-1);
		}
		close(fd[1]);
	}
	if (is_builtin(token[line->i].command[0]))
	{
		execute_builtin(&token[line->i], line); // Execute the built-in
		exit(line->err_num);
	}
	else
	{
		if (execve(line->paths[line->i], token[line->i].command, line->envp) == -1)
			exit(1);
	}
	return (in_fd);
}

static void	set_error(t_tokens *token, t_mini *line, int check)
{
	if (check == -1)
		line->err_num = 1;
	else if (token[line->i].command[0][0] == 9)
		line->err_num = 127;
	line->i++;
}

void	execute(t_tokens *token, t_mini *line)
{
	int		fd[2];
	pid_t	pid;
	int		in_fd;
	int		check;

	in_fd = dup(STDIN_FILENO);
	line->i = 0;
	if (line->pipe_num == 1 && is_builtin(token[line->i].command[0]))
		return (single_builtin(token, line, fd));
	while (line->i < line->pipe_num)
	{
		line->flag = 0;
		line->err_num = 0;
		if (line->i < line->pipe_num - 1 && pipe(fd) == -1)
			exit(1);
		// if (is_builtin(token[line->i].command[0]))
		// {
		// 	builtin_execution(token, line, in_fd, fd); // Execute the built-in
		// 	line->i++; // Move to the next command in the pipeline
		// 	continue ;
		// }
		check = redirections(&token[line->i]);
		if (check != -1 && !(is_builtin(token[line->i].command[0])))
		{
			if (get_path(token[line->i].command, line) == -1)
				malloc_failure(line);
		}
		else
		{
			line->paths[line->i] = ft_strdup("won't be used\n");
			if (!line->paths[line->i])
				malloc_failure(line);
		}
		if (check == -1 || token[line->i].command[0][0] == 9)
		{
			set_error(token, line, check);
			continue ;
		}
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
			in_fd = child(token, line, in_fd, fd);
		else
			in_fd = parent(in_fd, line, fd);
		line->i++;
	}
	wait_for_child(line);
}
