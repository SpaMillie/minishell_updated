/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:18:38 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/17 11:33:54 by tparratt         ###   ########.fr       */
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
		hostname = "unknown";
	prompt = ft_strdup(username);
	prompt = join_and_free(prompt, "@");
	prompt = join_and_free(prompt, hostname);
	prompt = join_and_free(prompt, ":");
	prompt = join_and_free(prompt, cwd);
	free(cwd);
	prompt = join_and_free(prompt, "$ ");
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	char				*line_read;
	char				*prompt;
	t_mini				line;
	t_tokens			*token;
	struct sigaction	sa;

	(void) argv;
	line = (t_mini){0};
	line.err_num = 0;
	line.envp = envp_dup(envp);
	if (!line.envp)
		malloc_failure();
	export("OLDPWD", &line);
	set_term_attr();
	if (argc == 1)
	{
		sa.sa_handler = handle_signal;
		sigaction(SIGINT, &sa, NULL);
		sigaction(SIGQUIT, &sa, NULL);
		while (1)
		{
			prompt = create_prompt();
			line_read = readline(prompt);
			if (!line_read)
				return (0);
			free(prompt);
			if (ft_strlen(line_read) == 0)
				continue ;
			add_history(line_read);
			validating(line_read, &line);
			here_doc(&line);
			expansion(&line);
			p_count(&line);
			token = malloc(sizeof(t_tokens) * (line.pipe_num));
			if (!token)
				malloc_failure();
			function(&line, token);
			execute(token, &line);
			free(line_read);
			free_2d(line.metaed);
			free_2d(line.element);
			free_2d(token->command);
			free_2d(token->redirect);
			free(token);
		}
	}
	else
		ft_putendl_fd("Minishell cannot take arguments", 2);
	return (0);
}
