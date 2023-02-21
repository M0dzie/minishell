/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:41:27 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/02/21 09:42:06 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_echo(t_msl *ms, char **args_cmd, char **envp)
{
	// if $? in parsing change this with ms->rtn_int
	// char	*tmp_arg[] = {"echo", ft_itoa(ms->rtn_int), NULL};
	// create_pipe(tmp_arg, ms, envp);

	// printf("Errno : %d\n", errno);
	
	create_pipe(args_cmd, ms, envp);
}
