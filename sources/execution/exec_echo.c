/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:41:27 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/02/21 14:49:58 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_echo(t_msl *ms, char **args_cmd, char **envp)
{
	// if $? in parsing change this with ms->rtn_int
	// char	*tmp_arg[] = {"echo", ft_itoa(ms->rtn_int), NULL};
	// create_pipe(tmp_arg, ms, envp);

	// printf("Errno : %d\n", errno);
	
	// create_pipe(args_cmd, ms, envp);
	handle_cmd(ms, args_cmd, envp);
}
