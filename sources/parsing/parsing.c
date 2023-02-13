/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:49:26 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/13 11:18:07 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_args(char **args)
{
	for (int i = 0; args[i]; i++)
		ft_printf("%s\n", args[i]);
}

void	read_prompt(char *input, char **env)
{
	char	**args;

	args = ft_split(input, ' ');
	print_args(args);
	parsing_errors(input);
	if (ms_strcmp(input, "pwd"))
		print_pwd();
	else if (ms_strcmp(input, "env"))
		print_env(env);
}

void	signal_handler(int signal)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}