/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:23:06 by thmeyer           #+#    #+#             */
/*   Updated: 2023/03/08 13:41:32 by thmeyer          ###   ########.fr       */
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
char	*get_after_quote(char *input, int index);
char	*get_before_quote(char *input, int index);
char	**ms_split(t_msl *ms, char *input);
char	*parsing_env_var(t_msl *ms, char *token);
char	*parsing_quotes_split(t_msl *ms, char *token);
char	*switch_var(t_msl *ms, char *token, int i);

int		check_opened_quotes(t_msl *ms, char *input, int i, char c);
int		check_sign(char *token, int i);
int		count_tokens(char *input);
int		display_errors(t_msl *ms, char *input, int type);
int		display_errors_pipe(t_msl *ms, char *input, int type);
int		display_errors_redirect(t_msl *ms, char *input, int type);
int		display_errors_redirect2(t_msl *ms, char *input, int type);
int		display_errors_redirect3(t_msl *ms, char *input, int type);
int		display_errors_redirect4(t_msl *ms, char *input, int type);
int		is_space(char c);
int		ms_strcmp(char *s1, char *s2);
int		parsing_errors(t_msl *ms, char *input, int c_pipe);
int		parsing_pipes_input(t_msl *ms);
int		parsing_quotes(t_msl *ms);

void	count_pipes(t_msl *ms);
void	parsing_echo(t_msl *ms, char *input, char **envp);

void	execution(t_msl *ms, char *input, char **envp);
void	create_pipe(char **args_cmd, t_msl *ms, char **envp);
char	*get_cmd_path(char *cmd, char **envp);
void	execute_cmd(char **cmd_args, char **envp);
int		display_error_exec(char *first, char *second, int num_error);
void	handle_cmd(t_msl *ms, char **tmp_args, char **envp);
void	init_env(t_msl *ms, char **envp);

void	exec_exit(t_msl *ms, char **args_cmd);
int		exec_pwd(t_msl *ms, char **args_cmd, char **envp);
void	exec_cd(t_msl *ms, char **args_cmd, char **envp);
int		exec_env(t_msl *ms, char **args_cmd, char **envp);
void	exec_echo(t_msl *ms, char **args_cmd, char **envp);
int		exec_export(t_msl *ms, char **args_cmd, char **envp);
int		exec_unset(t_msl *ms, char **args_cmd, char **envp);

void	parsing_errors_echo(t_msl *sl);
void	read_prompt(t_msl *ms, char **envp);
void	signal_handler(int signal);


void	print_args(char ***args);

#endif

