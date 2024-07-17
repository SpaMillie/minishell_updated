/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:18:20 by tparratt          #+#    #+#             */
/*   Updated: 2024/07/17 17:57:34 by tparratt         ###   ########.fr       */
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
# include <sys/ioctl.h>

extern int	g_sigflag;

# define PIPE 3
# define RED_IN 4
# define RED_OUT 5
# define DOLLAR 7

typedef struct s_mini
{
	char	**metaed;
	char	**element;
	char	**envp;
	char	**paths;
	int		pipe_num;
	int		err_num;
	int		flag;
	int		i;
	int		input_fd;
	int		output_fd;
}	t_mini;

typedef struct s_tokens
{
	char	**command;
	char	**redirect;
}	t_tokens;

typedef struct s_alloc
{
	int	redir;
	int	other;
}	t_alloc;

typedef struct s_fds
{
	int	in;
	int	out;
	int	close;
}	t_fds;

//builtin_check.c
void		execute_builtin(t_tokens *token, t_mini *line);
int			is_builtin(char *str);
//cd.c
void		cd(char **args, t_mini *line, t_tokens *token);
//children.c
t_fds		set_fds(t_mini *line, t_tokens *token, int *prev);
//echo-pwd-env.c
void		echo(char **args);
void		pwd(t_mini *line, t_tokens *token);
void		env(char **args, t_mini *line);
//exit.c
void		exit_cmd(char **args, t_mini *line, t_tokens *token);
//export.c
void		export_cmd(char **args, t_mini *line, t_tokens *token);
void		export(char *arg, t_mini *line, t_tokens *token);
//unset.c
void		unset_cmd(char **args, t_mini *line, t_tokens *token);
void		unset(char *arg, t_mini *line, t_tokens *token);
int			export_unset_error_check(char **args, t_mini *line);
//env.c
char		*ft_getenv(char **envp, char *str, t_mini *line, t_tokens *token);
char		*get_env_value(char **envp, char *str, t_mini *line,
				t_tokens *token);
//error.c
void		free_2d(char **tab);
void		malloc_failure(t_mini *line, t_tokens *token);
void		malloc_failure_without_token(t_mini *line);
void		malloc_failure_no_cleanup(void);
//execution.c
void		execute(t_tokens *token, t_mini *line);
//execution2.c
void		single_builtin(t_tokens *token, t_mini *line);
void		shell_lvl_check(t_mini *line, t_tokens *token);
void		wait_for_child(t_mini *line, t_tokens *token);
//expansion.c
void		expansion(t_mini *line);
//expansion2.c
char		*get_substring(char *s, int j);
int			dup_or_join(char **new_tokens, int loop, int i, char *str);
void		duplicate(t_mini *line, char **new_tokens);
char		*nothing_to_expand(t_mini *line, char **new_tokens, int loop,
				int j);
//fd_handling.c
int			init_fd(int *input, int *output);
int			close_cleanup(t_mini *line);
//first_split.c
int			first_split(char *argv, t_mini *line);
//heredoc.c
int			here_doc(t_mini *line);
char		*create_hd_name(int hd_num, t_mini *line);
//heredoc2.c
int			heredoc_strncmp(const char *s1, const char *s2, size_t n);
char		*here_strjoin(char *s1, char *s2);
int			ft_intlen(int n);
char		*null_hdoc_line(char *hdoc_line, char *delim, t_mini *line);
char		*hdoc_loop(char *hdoc_line, int fd, char *delim);
//opening_files.c
int			opening(t_tokens *token, t_mini *line);
//parsing.c
void		tokenising(t_mini *line, t_tokens *token);
void		p_count(t_mini *line);
//paths.c
int			get_path(char **tokens, t_mini *line, t_tokens *token);
//redirect.c
void		redirections(t_mini *line, t_tokens *token, t_fds *cur);
//restore_fds.c
int			dup2_in(int *input, int *other, int option);
int			dup2_out(int *output, int *other, int option);
//retrim.c
void		retrim_tokens(t_tokens *token);
//second_split.c
int			second_split(t_mini *line);
//signals.c
void		handle_ctrl_c(int signal);
void		set_term_attr(struct termios *tios);
void		reset_term_attr(struct termios *tios);
void		check_g_sigflag(t_mini *line);
void		handle_sigint(int signal);
void		handle_sigquit(int signal);
void		handle_heredoc_sig(int signal);
//syntax_errors.c
int			syntax_error(t_mini *line, char *s, int i);
int			check_syntax_errors(t_mini *line, int words);
//trim.c
void		trim_quotes(t_mini *line);
//utils.c
void		print_error(char *message, char **args);
char		**malloc_2d(char **arr);
char		**envp_dup(char **envp);
char		*build_prompt(char *username, char *hostname, char *cwd);
//utils2.c
void		cleanup(t_mini *line, t_tokens *token, int option);
void		print_2d(char **tab);
char		*join_and_free(char *prompt, char *str);
void		free_paths(t_mini *line);
//utils3.c
void		cleanup_close(t_mini *line, t_tokens *token);
int			has_input(t_tokens *token);
int			has_output(t_tokens *token);
void		unnecessary_path(t_mini *line, t_tokens *token);
int			empty_command(t_mini *line, char *line_read);
//utils4.c
char		*simple_itoa(int n);
void		free_before_return(t_mini *line, char *hd_name, int hd_num);
//validation.c
int			validating(char *argv, t_mini *line, char *line_read);
int			is_it_redirect(char *s);
int			is_it_space(char *s, int i);
int			ft_skip(char *s, int i);
//external
extern void	rl_replace_line(const char *text, int clear_undo);

#endif
