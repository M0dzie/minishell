/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:49:28 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/04/05 01:17:09 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_one(t_msl *ms, t_block *block)
{
	if (!fds_valid(ms, 0))
		ms->status = 1;
	if (block->arg)
		if (is_builtins_solo(block, block->arg->name) && fds_valid(ms, 0))
			builtins_execution(ms, block);
	ms->pid[0] = fork();
	if (ms->pid[0] < 0)
		display_error_exec("minishell: ", "fork", 15);
	if (ms->pid[0] == 0)
	{
		if (ms->blocks[0]->is_input && fds_valid(ms, 0))
			handle_input(ms, 0, 0);
		if (ms->blocks[0]->is_output && fds_valid(ms, 0))
			handle_output(ms, 0, 0);
		if (block->arg)
		{
			if (is_builtins(block->arg->name) && !is_builtins_solo(block,
					block->arg->name) && fds_valid(ms, 0))
				builtins_execution(ms, block);
			if (!is_builtins(block->arg->name) && fds_valid(ms, 0))
				execute_cmd(ms, block->args_cmd);
		}
		exit(ms->status);
	}
}

void	exec_last_cmd(t_msl *ms, int index)
{
	ms->pid[index] = fork();
	if (ms->pid[index] < 0)
		display_error_exec("minishell: ", "fork", 15);
	else if (ms->pid[index] == 0)
	{
		handle_input(ms, index, -1);
		handle_output(ms, index, -1);
		if (ms->blocks[index]->arg && fds_valid(ms, 0))
			distribute_cmd(ms, index);
		exit(ms->status);
	}
	else
	{
		close(ms->pipes[index - 1][1]);
		if (ms->blocks[index]->is_output)
			close(ms->blocks[index]->fd_out);
	}
}

void	exec_middle_cmd(t_msl *ms, int index)
{
	ms->pid[index] = fork();
	if (ms->pid[index] < 0)
		display_error_exec("minishell: ", "fork", 15);
	else if (ms->pid[index] == 0)
	{
		handle_input(ms, index, -1);
		handle_output(ms, index, 0);
		if (ms->blocks[index]->arg && fds_valid(ms, 0))
			distribute_cmd(ms, index);
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
		display_error_exec("minishell: ", "fork", 15);
	else if (ms->pid[index] == 0)
	{
		handle_input(ms, index, 0);
		handle_output(ms, index, 0);
		if (ms->blocks[index]->arg && fds_valid(ms, index))
			distribute_cmd(ms, index);
		exit(ms->status);
	}
	else
	{
		close(ms->pipes[index][1]);
		if (ms->blocks[index]->is_output)
			close(ms->blocks[index]->fd_out);
	}
}

void	exec_cmd(t_msl *ms, int i)
{
	if (ms->c_cmd == 1)
		exec_one(ms, ms->blocks[i]);
	else if (i == 0)
		exec_first_cmd(ms, i);
	else if (i == ms->c_cmd - 1)
		exec_last_cmd(ms, i);
	else
		exec_middle_cmd(ms, i);
}
