/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:18:20 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/13 14:29:02 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdio.h>
# include <termios.h>
# include <string.h>

typedef struct s_mini
{
	char	**metaed;
	char	**element;
	int		pipe_num;
	char	**envp;
	int		err_num;
	int		flag;
	int		i;
}				t_mini;

typedef struct s_tokens
{
	char	**command;
	char	**redirect;
}				t_tokens;

typedef struct s_alloc
{
	int	redir;
	int	other;
}				t_alloc;

void		free_2d(char **tab);
void		print_2d(char **tab);
char		*join_and_free(char *prompt, char *str);
char		**malloc_2d(char **arr);
char		**envp_dup(char **envp);
void		malloc_failure(void);
extern void	rl_replace_line(const char *text, int clear_undo);
void		execute(t_tokens *token, t_mini *line);
void		echo(char **args);
void		pwd(void);
void		cd(char **args, t_mini *line);
void		env(char **args, t_mini *line);
void		exit_cmd(char **args, t_mini *line);
void		export_cmd(char **args, t_mini *line);
void		export(char *arg, t_mini *line);
void		unset_cmd(char **args, t_mini *line);
void		unset(char *arg, t_mini *line);
char		*ft_getenv(char **envp, char *str);
char		*get_path(char **tokens, char **envp);
void		handle_signal(int signal);
void		set_term_attr(void);
void		expansion(t_mini *line);
void		validating(char *argv, t_mini *line);
int			is_it_redirect(char *s);
void		function(t_mini *line, t_tokens *token);
void		p_count(t_mini *line);
void		execute_command(t_tokens *token, t_mini *line);
void		execute_builtin(t_tokens *token, t_mini *line);
int			is_builtin(t_tokens *token);
int			first_split(char *argv, t_mini *line);
int			second_split(t_mini *line);
void		trim_quotes(t_mini *line);
int			is_it_space(char *s, int i);
int			ft_skip(char *s, int i);
int			is_whitespace(char c);
void		print_error(char *message, char **args);
int			export_unset_error_check(char **args, t_mini *line);
char		*get_env_value(char **envp, char *str, t_mini *line);
void		redirections(t_tokens *token);
void		here_doc(t_mini *line);
void		dup_or_join(char **new_tokens, int loop, int i, char *str);
void		duplicate(t_mini *line, char **new_tokens);
char		*get_substring(char *s, int j);

#endif