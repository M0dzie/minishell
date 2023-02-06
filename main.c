/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:38:17 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/06 19:19:25 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tamer(int sort)
{
	char	*output;

	if (sort == 1)
	{
		output = getenv("PWD");
		printf("PWD = %s\n", output);
	}
}

void	print_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n",env[i]);
}

void	read_prompt(char *input, char **env)
{
	if (ft_strncmp(input, "pwd", 3) == 0)
		print_tamer(1);
	else if (ft_strncmp(input, "env", 3) == 0)
		print_env(env);
	else
		ft_printf("input = %s\n", input);
}

int	main(int argc, char **argv, char **env)
{
	pid_t	pid;
	char	*input;

	(void) argv;
	if (argc != 1)
		return (ft_putendl_fd("Error\nminishell doesn't take any parameters.", \
		2), 0);
	while (1)
	{
		input = readline("$> ");
		add_history(input);
		read_prompt(input, env);
	}
	printf("pid = %d\n", pid);
	return (0);
}


	// pid = fork();
	// if (pid < 0)
	// 	return (ft_putendl_fd("Error\nNo child process was created.", 2), 0);