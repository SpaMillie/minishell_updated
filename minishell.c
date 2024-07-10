/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/10 14:36:58 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "minishell.h"

static char	*create_prompt(void)
{
	char	*cwd;
	char	*username;
	char	*hostname;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		exit(1);
	}
	username = getenv("USER");
	if (!username)
		username = "unknown";
	hostname = getenv("HOSTNAME");
	if (!hostname)
		hostname = "hive";
	prompt = build_prompt(username, hostname, cwd);
	return (prompt);
}

static void	to_token(t_mini *line, t_tokens **token)
{		
	p_count(line);
	*token = malloc(sizeof(t_tokens) * (line->pipe_num));
	if (!(*token))
		malloc_failure_without_token(line);
	tokenising(line, *token);
	if (init_fd(&line->input_fd, &line->output_fd) == -1)
	{
		cleanup(line, *token, 1);
		exit (1);
	}
}

static int	prompting(char **line_read)
{					
	char *prompt;

	prompt = create_prompt();
	*line_read = readline(prompt);
	if (!line_read)
		return (1); // NULL if failed to allocate?
	free(prompt);
	return (0);
}

static int	minishell_loop(t_mini *line)
{
	t_tokens	*token;
	char		*line_read;
	
	token = (t_tokens *){0};
	line_read = NULL;
	while (1)
	{			
		if (prompting(&line_read) == 1)
			return (1);
		if (!line_read)
			return (2);
		if (ft_strlen(line_read) == 0)
			continue ;
		add_history(line_read);
		if (validating(line_read, line, line_read) == 1)
			continue ;
		free(line_read);
		expansion(line);
		to_token(line, &token);
		execute(token, line);
		if (token->command[0] && ft_strncmp(token->command[0], "exit", ft_strlen(token->command[0])) == 0)
		{
			cleanup(line, token, 1);
			break ;
		}
		cleanup(line, token, 0);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini				line;
	struct sigaction	sa;
	int					check;

	(void)argv;
	// system("lsof -p $$");
	line = (t_mini){0};
	line.envp = envp_dup(envp);
	if (!line.envp)
		malloc_failure_no_cleanup();
	set_term_attr();
	if (argc == 1)
	{
		ft_memset(&sa, 0, sizeof(sa));
		sa.sa_handler = handle_signal;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
        sigaction(SIGINT, &sa, NULL);
        sigaction(SIGQUIT, &sa, NULL);
		check = minishell_loop(&line);
		if (check == 1)
			return (1);
		else if (check == 2)
			free_2d(line.envp);
	}
	else
		ft_putendl_fd("Minishell cannot take arguments", 2);
	return (0);
}
