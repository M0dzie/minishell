/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:49:28 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/03/27 22:11:20 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	distribute_cmd(t_msl *ms, int index)
{
	if (is_builtins(ms->blocks[index]->arg->name))
		builtins_execution(ms, ms->blocks[index]->arg, 1);
	else
		standard_execution(ms, ms->blocks[index]->arg);
}

void	handle_output(t_msl *ms, int index, int mode, int position)
{
	if (mode == 0)
	{
		if (ms->blocks[index]->is_output)
		{
			dup2(ms->blocks[index]->fd_out, STDOUT_FILENO);
			close(ms->blocks[index]->fd_out);
			// if (ms->blocks[index]->is_output == TRUNC)
			// {
			// 	// printf("dup2 file fd %d\n", ms->blocks[index]->fd_in);
			// 	dup2(ms->blocks[index]->fd_in, STDIN_FILENO);
			// 	close(ms->blocks[index]->fd_in);
			// }
			// else
			// 	printf("dup2 heredoc input\n");
		}
		else
		{
			dup2(ms->pipes[index + position][1], STDOUT_FILENO);
			// close(ms->pipes[index + position][1]);
		}
	}
	else if (mode == 1)
	{
	// 	if (ms->blocks[index]->is_output)
	// 	{
	// 		if (ms->blocks[index]->is_output == TRUNC)
	// 			// printf("close file fd\n");
	// 			close(ms->blocks[index]->fd_in);
	// 		// else
	// 		// 	printf("dup2 heredoc input\n");
	// 	}
		// else
		// 	close(ms->pipes[index + position][1]);
	}
}

void	handle_input(t_msl *ms, int index, int mode, int position)
{
	if (mode == 0)
	{
		if (ms->blocks[index]->is_input)
		{
			if (ms->blocks[index]->is_input == INPUT)
			{
				printf("dup2 file fd %d\n", ms->blocks[index]->fd_in);
				dup2(ms->blocks[index]->fd_in, STDIN_FILENO);
				close(ms->blocks[index]->fd_in);
			}
			else
				printf("dup2 heredoc input\n");
		}
		else
		{
			dup2(ms->pipes[index + position][0], STDIN_FILENO);
			// close(ms->pipes[index + position][0]);
		}
	}
	else if (mode == 1)
	{
		if (ms->blocks[index]->is_input)
		{
			if (ms->blocks[index]->is_input == INPUT)
				// printf("close file fd\n");
				close(ms->blocks[index]->fd_in);
			// else
			// 	printf("dup2 heredoc input\n");
		}
		else
			close(ms->pipes[index + position][0]);
			// close(ms->pipes[index + position][1]);
	}
}

void	exec_last_cmd(t_msl *ms, int index)
{
	ms->pid[index] = fork();
	if (ms->pid[index] < 0)
		display_error_exec("minishell: ", "fork", 15);
	else if (ms->pid[index] == 0)
	{
		handle_input(ms, index, CHILD, -1);
		handle_output(ms, index, CHILD, -1);
		if (ms->blocks[index]->arg)
			distribute_cmd(ms, index);
		exit(ms->status);
	}
	else
	{
		// close(ms->pipes[index - 1][0]);
		// handle_input(ms, index, PARENT, -1);
		// handle_output(ms, index, CHILD, -1);
		// close (ms->pipes[index][1]);
	}
}

void	exec_middle_cmd(t_msl *ms, int index)
{
	ms->pid[index] = fork();
	if (ms->pid[index] < 0)
		display_error_exec("minishell: ", "fork", 15);
	else if (ms->pid[index] == 0)
	{
		close(ms->pipes[index][0]);
		handle_input(ms, index, CHILD, -1);
		handle_output(ms, index, CHILD, 0);
		if (ms->blocks[index]->arg)
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
		close(ms->pipes[index][0]);
		handle_input(ms, index, CHILD, 0);
		
		dup2(ms->pipes[index][1], STDOUT_FILENO);
		close(ms->pipes[index][1]);


		if (ms->blocks[index]->arg)
			distribute_cmd(ms, index);
		exit(ms->status);
	}
	else
		close(ms->pipes[index][1]);
}

void	exec_pipe(t_msl *ms, int i_pid, int pos_in, int pos_out)
{
	ms->pid[i_pid] = fork();
	if (ms->pid[i_pid] < 0)
		display_error_exec("minishell: ", "fork", 15);
	else if (ms->pid[i_pid] == 0)
	{
		handle_input(ms, i_pid, CHILD, pos_in);
		handle_output(ms, i_pid, CHILD, pos_out);

		if (ms->blocks[i_pid]->arg)
			distribute_cmd(ms, i_pid);
		exit(ms->status);
	}
	// else
	// {
	// 	handle_input(ms, i_pid, PARENT, pos_in);
	// 	handle_output(ms, i_pid, PARENT, pos_out);
	// }
}

void	exec_cmd(t_msl *ms, int i)
{
	if (ms->c_cmd == 1)
		exec_one(ms, ms->blocks[i]->arg);
	else if (i == 0)
		exec_first_cmd(ms, i);
		// exec_pipe(ms, i, FIRST, FIRST);
	else if (i == ms->c_cmd - 1)
		exec_last_cmd(ms, i);
		// exec_pipe(ms, i, LAST, LAST);
	else
		exec_middle_cmd(ms, i);
}
