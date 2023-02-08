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
	else if (ms_strcmp(input, "echo"))
		printf("%s\n", input + 5);
}

char	*parsing_input(char *input)
{
	int	i;

	i = -1;
	if (input[0] == '$')
		return (printf("$\n"), input + 1);
	while (input[++i])
	{
		if (ms_strcmp((input + i), "|"))
			return (printf("Pipex\n"), input);
		if (ms_strcmp((input + i), "<<"))
			return (printf("<<\n"), input);
		if (ms_strcmp((input + i), "<"))
			return (printf("<\n"), input);
		if (ms_strcmp((input + i), ">>"))
			return (printf(">>\n"), input);
		if (ms_strcmp((input + i), ">"))
			return (printf(">\n"), input);
	}
	return (input);
}

void	signal_handler(int signal)
{
	if (signal == 2)
	{
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
}