/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:41:27 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/03/18 20:14:03 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
// #include "../../includes/minimehdi.h"

int	exec_echo(t_msl *ms, char **args_cmd)
{
	int	exit_stat;

	exit_stat = 0;
	execute_cmd(ms, args_cmd, ms->arrenv);
	return (exit_stat);
}
