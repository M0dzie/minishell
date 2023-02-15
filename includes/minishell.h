/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:23:06 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/15 19:13:11 by thmeyer          ###   ########.fr       */
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
	char	*input;
	char	**split;
	char	***cmds;
	int		c_pipe;
}				t_msl;

char	*del_quotes(t_msl *ms, char c);

int		check_opened_quotes(char *input, char c);
int		count_pipes(char *input);
int		ms_strcmp(char *s1, char *s2);
int		parsing_errors(t_msl *ms);
void	parsing_errors_echo(t_msl *sl);

void	display_errors(t_msl *ms, int type);
void	execution(t_msl *ms, char *input, char **envp);
void	read_prompt(t_msl *ms, char **envp);
void	signal_handler(int signal);

#endif