/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:49:26 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/13 12:28:16 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_args(char **args)
{
	for (int i = 0; args[i]; i++)
		printf("%s\n", args[i]);
}

void	read_prompt(char *input, char **env)
{
	int		i;
	char	**args;

	i = 0;
	args = ft_split(input, ' ');
	print_args(args);
	parsing_errors(input);
	if (ms_strcmp(args[i], "pwd"))
		print_pwd();
	else if (ms_strcmp(args[i], "env"))
		print_env(env);
	else
		printf("Command '%s' not found.\n", args[i]);
}
// faire une fonction pour savoir si la commande existe, else -> msg error.
// faire ca pour chaque arguments avec un i++ dans le printf ?
// Faire un decompte d'erreurs ? Du genre j'envoie 1 pour chaque arg valable, et
// si la somme n'est pas egal au nb de split -> faux ?

void	signal_handler(int signal)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}