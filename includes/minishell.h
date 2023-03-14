/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:23:06 by thmeyer           #+#    #+#             */
/*   Updated: 2023/03/14 09:34:51 by thmeyer          ###   ########.fr       */
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

typedef struct s_var
{
	char			*name;
	char			*value;
	int				in_env;
	struct s_var	*next;
}					t_var;

typedef struct s_msl
{
	char	*input;
	char	**split;
	char	***cmds;
	int		c_pipe;
	int		lst_quote;
	int		f_quote;
	int		status;
	int		c_cmd;
	t_var	*env;
	t_var	*export;
	pid_t	pid;
}			t_msl;

char	*clear_line(char *before_line, char *new_word, char *next_line);
char	*del_quotes(char *input, int index, int lst_quote, char c);
char	**ft_getenv(t_msl *ms, int mode);
char	*get_after_delim(char *input, int index);
char	*get_before_delim(char *input, int index);
char	*get_cmd_path(char *cmd, char **envp);
char	**ms_split(t_msl *ms, char *input);
char	*parsing_env_var(t_msl *ms, char *token);
char	*parsing_quotes_split(t_msl *ms, char *token);
char	**split_equal(char *env_var);
char	*switch_var(t_msl *ms, char *token, int i);

int		check_opened_quotes(t_msl *ms, char *input, int i, char c);
int		check_sign(char *token, int i);
int		count_tokens(char *input);
int		display_error_exec(char *first, char *second, int num_error);
int		display_errors(t_msl *ms, char *input, int type);
int		display_errors_pipe(t_msl *ms, char *input, int type);
int		display_errors_redirect(t_msl *ms, char *input, int type);
int		display_errors_redirect2(t_msl *ms, char *input, int type);
int		display_errors_redirect3(t_msl *ms, char *input, int type);
int		display_errors_redirect4(t_msl *ms, char *input, int type);
int		envsize(t_msl *ms);
int		exec_env(t_msl *ms, char **args_cmd, char **envp);
int		exec_export(t_msl *ms, char **args_cmd, char **envp);
int		exec_pwd(t_msl *ms, char **args_cmd, char **envp);
int		exec_unset(t_msl *ms, char **args_cmd, char **envp);
int		invalid_first(char *name);
int		is_space(char c);
int		parsing_errors(t_msl *ms, char *input, int c_pipe);
int		parsing_pipes_input(t_msl *ms);
int		parsing_quotes(t_msl *ms);
int		strict_cmp(const char *builts, const char *cmd);

t_var	*getvar(t_msl *ms, char *name);
t_var	*new_var(char *name, char *value, int in_env);

void	count_pipes(t_msl *ms);
void	create_pipe(char **args_cmd, t_msl *ms, char **envp);
void	display_env(t_msl *ms, int mode);
void	display_export(t_msl *ms);
void	execute_cmd(char **cmd_args, char **envp);
void	execution(t_msl *ms, char *input, char **envp);
void	exec_cd(t_msl *ms, char **args_cmd, char **envp);
void	exec_echo(t_msl *ms, char **args_cmd, char **envp);
void	exec_exit(t_msl *ms, char **args_cmd);
void	handle_cmd(t_msl *ms, char **tmp_args, char **envp);
void	init_env(t_msl *ms, char **envp);
void	parsing_echo(t_msl *ms, char *input, char **envp);
void	parsing_errors_echo(t_msl *sl);
void	pipe_one(char **args_cmd, t_msl *ms, char **envp);
void	read_prompt(t_msl *ms, char **envp);
void	signal_handler(int signal);
void	var_add_back(t_msl *ms, t_var *var);


void	print_args(char ***args);

#endif

