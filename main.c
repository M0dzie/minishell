/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:38:17 by thmeyer           #+#    #+#             */
/*   Updated: 2023/01/30 11:45:25 by thmeyer          ###   ########.fr       */
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

// char	*read_prompt(void)
// {
// 	char	*line;

// 	line = readline();
// 	if (line)
// 		add_history(line);
// 	else
// 		exit(0);
// 	return (line);
// }

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 1)
		return (ft_putendl_fd("Error\nminishell doesn't take any parameters.", \
		2), 0);
	(void) argv;
	pid = fork();
	if (pid < 0)
		return (ft_putendl_fd("Error\nNo child process was created.", 2), 0);
	else if (pid == 0)
		printf("#### Welcome to Child ####\n");
	else
		printf("#### Welcome to Parent ####\n");
	printf("pid = %d\n", pid);
	print_pwd();
	return (0);
}

// while (1)
// {
// }