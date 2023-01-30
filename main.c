/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:38:17 by thmeyer           #+#    #+#             */
/*   Updated: 2023/01/30 11:01:04 by thmeyer          ###   ########.fr       */
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

// char	*read_prompt(char *str)
// {
// 	char	*line;

// 	line = readline();
// 	return (line);
// }

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 1)
		return (ft_putendl_fd("Error\nminishell doesn't take any parameters.", \
		2), 0);
	(void) argv;
	// while (1)
	// {
	pid = fork();
	if (pid < 0)
		return (ft_putendl_fd("Error\nNo child process was created.", 2), 0);
	printf("pid = %d\n", pid);
	print_pwd();
	wait(NULL);
	// }
	return (0);
}
