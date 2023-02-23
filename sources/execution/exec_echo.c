/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:41:27 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/02/23 13:32:41 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minimehdi.h"

void	exec_echo(t_msl *ms, char **args_cmd, char **envp)
{
	// if $? in parsing change this with ms->rtn_int
	// char	*tmp_arg[] = {"echo", ft_itoa(ms->rtn_int), NULL};
	// create_pipe(tmp_arg, ms, envp);

	// printf("Errno : %d\n", errno);
	
	// create_pipe(args_cmd, ms, envp);
	if (strict_cmp(args_cmd[1], "$?"))
		printf("%d\n", ms->status);
	else
		handle_cmd(ms, args_cmd, envp);
}
