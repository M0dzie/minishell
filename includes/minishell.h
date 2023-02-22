/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:23:06 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/22 14:08:39 by thmeyer          ###   ########.fr       */
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
	struct s_var	*next;
}					t_var;

typedef struct s_msl
{
	char	*input;
	char	**split;
	char	***cmds;
	int		c_pipe;
	int		lst_quote;
	int		rtn_int;
	int		c_cmd;
	t_var	*env;
	pid_t	pid;
}			t_msl;

char	*clear_line(char *before_line, char *new_word, char *next_line);
char	*del_quotes(char *input, int index, int lst_quote, char c);
char	*get_after_quote(char *input, int index);
char	*get_before_quote(char *input, int index);

int		check_opened_quotes(t_msl *ms, int i, char c);
int		display_errors(t_msl *ms, int type);
int		display_errors_pipe(t_msl *ms, int type);
int		display_errors_redirect(t_msl *ms, int type);
int		display_errors_redirect2(t_msl *ms, int type);
int		display_errors_redirect3(t_msl *ms, int type);
int		display_errors_redirect4(t_msl *ms, int type);
int		ms_strcmp(char *s1, char *s2);
int		parsing_errors(t_msl *ms);
int		parsing_pipes_input(t_msl *ms);
int		parsing_quotes(t_msl *ms);

void	count_pipes(t_msl *ms);
void	parsing_echo(t_msl *ms);

void	execution(t_msl *ms, char *input, char **envp);
void	create_pipe(char **args_cmd, t_msl *ms, char **envp);
char	*get_cmd_path(char *cmd, char **envp);
void	execute_cmd(char **cmd_args, char **envp);
int		display_error_exec(char *first, char *second, int num_error);
void	handle_cmd(t_msl *ms, char **tmp_args, char **envp);
void	init_env(t_msl *ms, char **envp);

void	exec_exit(t_msl *ms, char **args_cmd);
void	exec_pwd(t_msl *ms, char **args_cmd, char **envp);
void	exec_cd(t_msl *ms, char **args_cmd, char **envp);
void	exec_env(t_msl *ms, char **args_cmd, char **envp);
void	exec_echo(t_msl *ms, char **args_cmd, char **envp);
void	exec_export(t_msl *ms, char **args_cmd, char **envp);
void	exec_unset(t_msl *ms, char **args_cmd, char **envp);

void	parsing_errors_echo(t_msl *sl);
void	read_prompt(t_msl *ms, char **envp);
void	signal_handler(int signal);


void	print_args(char ***args);

#endif

