/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:23:06 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/14 15:56:21 by thmeyer          ###   ########.fr       */
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

typedef struct s_msl
{
	char	**split;
	char	***cmds;
	int		c_pipe;
}				t_msl;

int		check_opened_quotes(char *input, char c);
int		check_wrong_quotes_echo(char *input);
int		count_pipes(char *input);
int		ms_strcmp(char *s1, char *s2);
int		parsing_errors(char *input);

void	print_pwd(void);
void	print_env(char **envp);
void	read_prompt(char *input, char **envp, t_msl *ms);
void	signal_handler(int signal);

#endif