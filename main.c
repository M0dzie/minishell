/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:38:17 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/06 18:29:21 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pwd(void)
{
	char	pwd[1024];

	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
}

// void	print_env()
// {
// 	getenv();
// }

void	read_prompt(char *input)
{
	ft_printf("input = %s\n", input);
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	char	*input;

	(void) input;
	(void) argv;
	if (argc != 1)
		return (ft_putendl_fd("Error\nminishell doesn't take any parameters.", \
		2), 0);
	while (1)
	{
		input = readline("$> ");
		add_history(input);
		read_prompt(input);
	}
	printf("pid = %d\n", pid);
	return (0);
}


	// pid = fork();
	// if (pid < 0)
	// 	return (ft_putendl_fd("Error\nNo child process was created.", 2), 0);