/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:38:17 by thmeyer           #+#    #+#             */
/*   Updated: 2023/01/30 09:37:46 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	printf("pid = %d\n", pid);
	return (0);
}
