/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:49:28 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/03/21 13:28:30 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_last_cmd(t_msl *ms, int index)
{
	ms->pid[index] = fork();
	if (ms->pid[index] < 0)
		display_error_exec("bash: ", "fork", 15);
	else if (ms->pid[index] == 0)
	{
		close(ms->pipes[index - 1][1]);
		dup2(ms->pipes[index - 1][0], STDIN_FILENO);
		close(ms->pipes[index - 1][0]);
		if (ms->blocks[index]->arg)
		{
			if (is_builtins(ms->blocks[index]->arg->name))
				builtins_execution(ms, ms->blocks[index]->arg, 1);
			else
				standard_execution(ms, ms->blocks[index]->arg);
		}
		exit(ms->status);
	}
	else
		close(ms->pipes[index - 1][0]);
}

void	exec_middle_cmd(t_msl *ms, int index)
{
	ms->pid[index] = fork();
	if (ms->pid[index] < 0)
		display_error_exec("bash: ", "fork", 15);
	else if (ms->pid[index] == 0)
	{
		close(ms->pipes[index][0]);
		dup2(ms->pipes[index - 1][0], STDIN_FILENO);
		close(ms->pipes[index - 1][0]);
		dup2(ms->pipes[index][1], STDOUT_FILENO);
		close(ms->pipes[index][1]);
		if (ms->blocks[index]->arg)
		{
			if (is_builtins(ms->blocks[index]->arg->name))
				builtins_execution(ms, ms->blocks[index]->arg, 1);
			else
				standard_execution(ms, ms->blocks[index]->arg);
		}
		exit(ms->status);
	}
	else
	{
		close(ms->pipes[index - 1][0]);
		close(ms->pipes[index][1]);
	}
}

void	exec_first_cmd(t_msl *ms, int index)
{
	ms->pid[index] = fork();
	if (ms->pid[index] < 0)
		display_error_exec("bash: ", "fork", 15);
	else if (ms->pid[index] == 0)
	{
		close(ms->pipes[index][0]);
		dup2(ms->pipes[index][1], STDOUT_FILENO);
		close(ms->pipes[index][1]);
		if (ms->blocks[index]->arg)
		{
			if (is_builtins(ms->blocks[index]->arg->name))
				builtins_execution(ms, ms->blocks[index]->arg, 1);
			else
				standard_execution(ms, ms->blocks[index]->arg);
		}
		exit(ms->status);
	}
	else
		close(ms->pipes[index][1]);
}

void	exec_cmd(t_msl *ms, int i)
{
	if (ms->c_cmd == 1)
		exec_one(ms, ms->blocks[i]->arg, i);
	else if (i == 0)
		exec_first_cmd(ms, i);
	else if (i == ms->c_cmd - 1)
		exec_last_cmd(ms, i);
	else
		exec_middle_cmd(ms, i);
}
