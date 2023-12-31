/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:23:06 by thmeyer           #+#    #+#             */
/*   Updated: 2023/04/05 02:21:01 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft/includes/libft.h"
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>

extern int		g_signal;

# define CMD 0
# define ARG 1
# define INPUT 2
# define HEREDOC 3
# define APPEND 4
# define TRUNC 5

# define ENV 0
# define EXPORT 1

# define BEFORE 0
# define AFTER 1

typedef struct s_var
{
	char			*name;
	char			*value;
	int				in_env;
	struct s_var	*next;
}					t_var;

typedef struct s_elem
{
	char			*name;
	int				type;
	struct s_elem	*next;
}					t_elem;

typedef struct s_block
{
	t_elem	*arg;
	t_elem	*in;
	t_elem	*out;
	char	*input;
	char	**args_cmd;
	int		fd_in;
	int		fd_out;
	int		is_input;
	int		is_output;
	int		index;
	int		cmd_found;
}			t_block;

typedef struct s_msl
{
	char	*input;
	char	*print_sig;
	char	**arrenv;
	char	**arrexport;
	char	**tokens;
	int		c_pipe;
	int		lst_delim;
	int		fst_delim;
	int		c_cmd;
	int		status;
	int		**pipes;
	pid_t	*pid;
	t_block	**blocks;
	t_var	*env;
}			t_msl;

char	*clear_line(char *before_line, char *new_word, char *next_line);
char	*del_quotes(char *input, int index, int lst_delim, char c);
char	**ft_getenv(t_msl *ms);
char	**ft_getexport(t_msl *ms);
char	**getarr_cmd(t_elem *arg);
char	*get_after_delim(char *input, int index);
char	*get_before_delim(char *input, int index);
char	*get_homepath(t_msl *ms);
char	*get_trim_path(t_msl *ms, char *path);
char	*parsing_env_var(t_msl *ms, char *token);
char	*parsing_quotes_split(t_msl *ms, char *token);
char	**split_equal(char *env_var);
char	*switch_var(t_msl *ms, char *token, int i);

int		check_arg_cd(t_msl *ms, char **args_cmd);
int		check_opened_quotes(t_msl *ms, char *input, int i, char c);
int		check_output(t_msl *ms, t_block *block);
int		check_input(t_msl *ms, t_block *block);
int		count_tokens(char *input);
int		display_error_exec(char *first, char *second, int num_error);
int		display_errors(t_msl *ms, char *input, int type);
int		display_errors_redirect(t_msl *ms, char *input, int type);
int		envsize(t_msl *ms, int mode);
int		exec_cd(t_msl *ms, char **args_cmd);
int		exec_echo(t_msl *ms, char **args_cmd);
int		exec_env(t_msl *ms, char **args_cmd);
int		exec_export(t_msl *ms, char **args_cmd);
int		exec_pwd(t_msl *ms, char **args_cmd);
int		exec_unset(t_msl *ms, char **args_cmd);
int		fds_valid(t_msl *ms, int index);
int		invalid_identifier(char *name);
int		invalid_identifier_unset(char *name);
int		is_builtins_solo(t_block *block, char *cmd);
int		is_builtins(char *cmd);
int		is_even(t_msl *ms, char *token, char quote);
int		is_heredoc(t_block *block);
int		is_in_quote(t_msl *ms, char *input, int in_quote);
int		is_token_delimiter(char input);
int		is_underscore(char *var_env);
int		len_env(char *env, int mode);
int		match_multi(char *s1, char *s2, char *s3, char *cmd);
int		parsing_errors(t_msl *ms, char *input, int c_pipe);
int		parsing_quotes(t_msl *ms);

t_var	*getvar(t_msl *ms, char *name);
t_var	*new_var(char *name, char *value, int in_env);
t_var	*new_varenv(char *env, int in_env);

void	builtins_execution(t_msl *ms, t_block *block);
void	display_env(t_msl *ms, int mode);
void	distribute_cmd(t_msl *ms, int index);
void	elem_addback(t_elem **stack, t_elem *new_elem);
void	execute_cmd(t_msl *ms, char **cmd_args);
void	execution(t_msl *ms);
void	exec_cmd(t_msl *ms, int i);
void	exec_exit(t_msl *ms, char **args_cmd);
void	exec_signal(void);
void	free_env(t_msl *ms);
void	free_exec(t_msl *ms);
void	free_global(t_msl *ms);
void	get_heredoc(t_msl *ms, t_block *block, int saveit);
void	handle_input(t_msl *ms, int index, int position);
void	handle_output(t_msl *ms, int index, int position);
void	init_env(t_msl *ms, char **envp);
void	input_signal(void);
void	ms_strtok(t_msl *ms, char *input);
void	parsing_exec(t_msl *ms);
void	read_prompt(t_msl *ms, char **envp);
void	update_arr(t_msl *ms);
void	var_add_back(t_var **stack, t_var *var);

t_elem	*new_elem(char *name, int type);

#endif
