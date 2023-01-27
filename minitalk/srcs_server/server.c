/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:14:58 by thmeyer           #+#    #+#             */
/*   Updated: 2023/01/27 15:25:51 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handling_size(int sig, int size, int *index)
{
	static int	bit = 32;

	if (sig == 30)
		size = size * 2 + 0;
	else
		size = size * 2 + 1;
	bit--;
	if (bit == 0)
	{
		*index = 1;
		bit = 32;
	}		
	return (size);
}

char	*handling_char(int sig, int size, char *str, int *index)
{
	static int	i = 0;
	static int	bit = 8;
	static char	c = 0;

	if (sig == 30)
		c = c * 2 + 0;
	else
		c = c * 2 + 1;
	bit--;
	if (bit == 0)
	{
		str[i] = c;
		bit = 8;
		c = 0;
		i++;
	}
	if (i == size)
	{
		str[i] = '\0';
		*index = 3;
		i = 0;
	}
	return (str);
}

void	receive_signal(int sig)
{
	static char	*str = NULL;
	static int	index = 0;
	static int	size = 0;

	if (index == 0)
		size = handling_size(sig, size, &index);
	else if (index == 1)
	{
		str = malloc(sizeof(char) * (size + 1));
		if (!str)
			exit(0);
		index = 2;
	}
	if (index == 2)
		str = handling_char(sig, size, str, &index);
	if (index == 3)
	{
		size = 0;
		index = 0;
		ft_printf("%s\n", str);
		free(str);
		str = NULL;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 1 && argv[0][0] != '\0')
		return (ft_printf("Error\nServer does not take parameters"), 0);
	ft_printf("PID : %d\n", getpid());
	signal(SIGUSR1, receive_signal);
	signal(SIGUSR2, receive_signal);
	while (1)
		pause();
	return (0);
}
