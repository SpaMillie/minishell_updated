/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:13:45 by mspasic           #+#    #+#             */
/*   Updated: 2024/07/19 13:00:38 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sigflag;

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

static int	prompting(char **line_read, struct termios tios, t_mini *line)
{					
	char	*prompt;

	prompt = ft_strdup("minishell> ");
	if (!prompt)
	{
		free_2d(line->envp);
		ft_putendl_fd("minishell: malloc failure", 2);
		exit(1);
	}
	set_term_attr(&tios);
	*line_read = readline(prompt);
	free(prompt);
	check_g_sigflag(line);
	if (!(*line_read))
		return (1);
	return (0);
}

static int	all_whitespace(char *line_read)
{
	int	i;

	i = 0;
	while (line_read[i])
	{
		if (!is_it_space(line_read, i))
			i++;
		else
			return (1);
	}
	return (0);
}

static int	minishell_loop(t_mini *line, struct termios tios)
{
	t_tokens	*token;
	char		*line_read;

	token = (t_tokens *){0};
	line_read = NULL;
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{	
		if (prompting(&line_read, tios, line) == 1)
			return (1);
		if (line_read && ft_strlen(line_read) && all_whitespace(line_read))
			add_history(line_read);
		if (validating(line_read, line) == 1)
		{
			free(line_read);
			continue ;
		}
		free(line_read);
		expansion(line);
		to_token(line, &token);
		execute(token, line);
		cleanup(line, token, 0);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_mini				line;
	struct termios		tios;

	(void)argv;
	line = (t_mini){0};
	g_sigflag = 0;
	line.envp = envp_dup(envp);
	if (!line.envp)
		malloc_failure_no_cleanup();
	if (argc == 1)
	{
		tcgetattr(0, &tios);
		if (minishell_loop(&line, tios) == 1)
		{
			free_2d(line.envp);
			return (1);
		}
	}
	else
		ft_putendl_fd("Minishell cannot take arguments", 2);
	return (0);
}
