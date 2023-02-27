/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:41:27 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/02/27 12:07:09 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minimehdi.h"

void	exec_echo(t_msl *ms, char **args_cmd, char **envp)
{
	if (strict_cmp(args_cmd[1], "$?"))
		printf("%d\n", ms->status);
	else
		handle_cmd(ms, args_cmd, envp);
}
