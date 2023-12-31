/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:15:45 by msapin            #+#    #+#             */
/*   Updated: 2023/04/04 14:15:56 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_option(char *arg)
{
	int	i;

	if (!arg)
		return (0);
	i = 0;
	if (arg[0] == '-')
	{
		while (arg[++i])
		{
			if (arg[i] != 'n')
				return (0);
		}
		return (1);
	}
	return (0);
}

int	exec_echo(t_msl *ms, char **args_cmd)
{
	int	exit_stat;
	int	i;
	int	nb_arg;
	int	n_option;

	nb_arg = ft_arrlen(args_cmd);
	exit_stat = 0;
	n_option = 1;
	while (is_valid_option(args_cmd[n_option]))
		n_option++;
	i = n_option;
	while (args_cmd[i])
	{
		ft_printf("%s", args_cmd[i]);
		if (i != nb_arg - 1)
			ft_printf(" ");
		i++;
	}
	if (n_option == 1)
		ft_printf("\n");
	return (exit_stat);
}
