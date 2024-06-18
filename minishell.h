/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:18:20 by tparratt          #+#    #+#             */
/*   Updated: 2024/06/15 14:47:35 by mspasic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/include/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdio.h>
# include <termios.h>
# include <string.h>

// typedef struct s_expansion_data
// {
// 	char	**new_tokens;
// 	int		loop;
// 	int		i;
// 	int		j;
// }				t_expansion_data;

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

//builtin_check.c
void		execute_builtin(t_tokens *token, t_mini *line);
int			is_builtin(char *str);
//cd.c
void		cd(char **args, t_mini *line);
//echo-pwd-env.c
void		echo(char **args);
void		pwd(void);
void		env(char **args, t_mini *line);
void		exit_cmd(char **args, t_mini *line);
//exit.c
void		exit_cmd(char **args, t_mini *line);
//export.c
void		export_cmd(char **args, t_mini *line);
void		export(char *arg, t_mini *line);
//unset.c
void		unset_cmd(char **args, t_mini *line);
void		unset(char *arg, t_mini *line);
int			export_unset_error_check(char **args, t_mini *line);
//env.c
char		*ft_getenv(char **envp, char *str);
char		*get_env_value(char **envp, char *str, t_mini *line);
//error.c
void		free_2d(char **tab);
void		malloc_failure(t_mini *line);
void		void_malloc_failure(void);
int			syntax_error(t_mini *line, char *s, int i);
//execution.c
void		execute(t_tokens **token, t_mini *line);
//expansion.c
void		expansion(t_mini *line);
//expansion2.c
char		*get_substring(char *s, int j);
void		dup_or_join(char **new_tokens, int loop, int i, char *str);
void		duplicate(t_mini *line, char **new_tokens);
//first_split.c
int			first_split(char *argv, t_mini *line);
//heredoc.c
void    	here_doc(t_mini *line);
//parsing.c
void		tokenising(t_mini *line, t_tokens *token);
void		p_count(t_mini *line);
//paths.c
char		*get_path(char **tokens, char **envp);
//redirect.c
void		redirections(t_tokens *token);
//second_split.c
int			second_split(t_mini *line);
//signals.c
void		handle_signal(int signal);
void		set_term_attr(void);
//trim.c
void		trim_quotes(t_mini *line);
//utils.c
int			is_whitespace(char c);
void		print_error(char *message, char **args);
char		**malloc_2d(char **arr);
char		**envp_dup(char **envp);
//utils2.c
void		cleanup(t_mini *line, t_tokens **token, char *line_read, int option);
void		print_2d(char **tab);
char		*join_and_free(char *prompt, char *str);
//validation.c
int			validating(char *argv, t_mini *line);
int			is_it_redirect(char *s);
int			is_it_space(char *s, int i);
int			ft_skip(char *s, int i);
//external
extern void	rl_replace_line(const char *text, int clear_undo);
// void		execute_command(t_tokens *token, t_mini *line);

#endif
