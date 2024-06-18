/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:18:38 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/17 15:15:42 by tparratt         ###   ########.fr       */
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
		exit(1);
	username = getenv("USER");
	if (!username)
		username = "unknown";
	hostname = getenv("HOSTNAME");
	if (!hostname)
		hostname = "hive";
	prompt = ft_strdup(username);
	prompt = join_and_free(prompt, "@");
	prompt = join_and_free(prompt, hostname);
	prompt = join_and_free(prompt, ":");
	prompt = join_and_free(prompt, cwd);
	free(cwd);
	prompt = join_and_free(prompt, "$ ");
	return (prompt);
}

static void	to_token(t_mini *line, t_tokens **token)
{			
		p_count(line);
		*token = malloc(sizeof(t_tokens) * (line->pipe_num));
		if (!(*token))
			malloc_failure(line);
		tokenising(line, *token);
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
	// printf("entered minishell_loop\n");
	while (1)
	{			
		if (prompting(&line_read) == 1)
			return (1);
		// printf("read line is %s\n", line_read);
		if (!line_read)
			return (2);
		if (ft_strlen(line_read) == 0)
			continue ;
		add_history(line_read);
		if (validating(line_read, line) == 1)
			continue ;
		expansion(line);
		to_token(line, &token);
		// printf("arrived here %s\n", token->command[0]);
		execute(&token, line);
		// printf("does it reach here?\n");
		// printf("here %s\n", token->command[0]);
		if (token->command[0] && ft_strncmp(token->command[0], "exit", ft_strlen(token->command[0])) == 0)
		{
			cleanup(line, &token, line_read, 1);
			break ;
		}
		cleanup(line, &token, line_read, 0);
		// printf("does it clean up?\n");
	}
	// printf("exited minishell_loop\n");
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini				line;
	struct sigaction	sa;
	int					check;

	(void)argv;
	line = (t_mini){0};
	line.envp = envp_dup(envp);
	if (!line.envp)
		malloc_failure(&line); //figure out what to free
	export("OLDPWD", &line);
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
