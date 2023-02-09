/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:49:26 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/09 11:03:31 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	read_prompt(char *input, char **env)
{
	parsing_errors(input);
	if (ms_strcmp(input, "pwd"))
		print_pwd();
	else if (ms_strcmp(input, "env"))
		print_env(env);
}

void	parsing_errors(char *input)
{
	int	i;
	int	status;

	status = 1;
	i = -1;
	while (input[++i])
	{
		if ((input[i] == 34 || input[i] == 39) && status == 1)
			checking_quotes(input, input[i], &status);
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