/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/0):46:09 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/07 13:56:43 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_prompt(char *input, char **env)
{
	if (ms_strcmp(input, "pwd"))
		print_pwd();
	else if (ms_strcmp(input, "env"))
		print_env(env);
}

void	parsing_input(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == 34 || input[i] == 39)
			checking_errors(input);
	}
}

void	signal_handler(int signal)
{
	if (signal == 2)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}