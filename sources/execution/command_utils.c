/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:52:15 by msapin            #+#    #+#             */
/*   Updated: 2023/04/05 01:15:35 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	distribute_cmd(t_msl *ms, int index)
{
	if (is_builtins(ms->blocks[index]->arg->name))
		builtins_execution(ms, ms->blocks[index]);
	else
		execute_cmd(ms, ms->blocks[index]->args_cmd);
}

int	fds_valid(t_msl *ms, int index)
{
	if (ms->blocks[index]->fd_in < 0 || ms->blocks[index]->fd_out < 0)
		return (0);
	return (1);
}

int	is_builtins_solo(t_block *block, char *cmd)
{
	if (!cmd || !cmd[0])
		return (0);
	if (ft_strmatch("cd", cmd) | ft_strmatch("unset", cmd)
		| (ft_strmatch("export", cmd) && block->arg->next != NULL)
		| ft_strmatch("exit", cmd))
		return (1);
	return (0);
}

int	is_builtins(char *cmd)
{
	if (!cmd || !cmd[0])
		return (0);
	if (match_multi("/usr/bin/echo", "/bin/echo", "echo", cmd)
		| match_multi("/usr/bin/pwd", "/bin/pwd", "pwd", cmd)
		| match_multi("/usr/bin/env", "/bin/env", "env", cmd)
		| ft_strmatch("cd", cmd) | ft_strmatch("unset", cmd)
		| ft_strmatch("export", cmd) | ft_strmatch("exit", cmd))
		return (1);
	return (0);
}

int	match_multi(char *s1, char *s2, char *s3, char *cmd)
{
	if (ft_strmatch(s1, cmd) || ft_strmatch(s2, cmd)
		|| ft_strmatch(s3, cmd))
		return (1);
	return (0);
}
