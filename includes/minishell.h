/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:23:06 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/13 14:42:10 by thmeyer          ###   ########.fr       */
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

typedef struct s_minishell
{
	char	**split;
	char	***args;
	int		c_pipe;
}				t_minishell;


int		count_pipes(char *input);
int		ms_strcmp(char *s1, char *s2);

void	checking_quotes(char *input, char c, int *status);
void	parsing_errors(char *input);
void	print_pwd(void);
void	print_env(char **envp);
void	read_prompt(char *input, char **envp, t_minishell *ms);
void	signal_handler(int signal);

#endif