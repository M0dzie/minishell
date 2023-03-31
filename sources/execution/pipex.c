/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:49:28 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/03/31 13:51:57 by msapin           ###   ########.fr       */
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

void	dupclose(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}

void	handle_output(t_msl *ms, int index, int mode, int position)
{
	if (mode == 0)
	{
		if (ms->blocks[index]->is_output)
			dupclose(ms->blocks[index]->fd_out, STDOUT_FILENO);
		else
			dupclose(ms->pipes[index + position][1], STDOUT_FILENO);
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
			// close(ms->pipes[index + position][1]);
	}
}

void	dupheredoc(t_msl *ms, int index)
{
	int	tmp_pipe[2];

	pipe(tmp_pipe);
	dup2(tmp_pipe[0], 0);
	write(tmp_pipe[1], ms->blocks[index]->input, ft_strlen_null(ms->blocks[index]->input));
	free(ms->blocks[index]->input);
	close(tmp_pipe[1]);
}

void	handle_input(t_msl *ms, int index, int mode, int position)
{
	if (mode == 0)
	{
		if (ms->blocks[index]->is_input)
		{
			if (ms->blocks[index]->is_input == INPUT)
				dupclose(ms->blocks[index]->fd_in, STDIN_FILENO);
			else
				dupheredoc(ms, index);
		}
		else
			dupclose(ms->pipes[index + position][0], STDIN_FILENO);
	}
	else if (mode == 1)
	{
		if (ms->blocks[index]->is_input)
		{
			if (ms->blocks[index]->is_input == INPUT)
				close(ms->blocks[index]->fd_in);
		}
		else if (position == 2)
		{
			close(ms->pipes[index - 1][0]);
			close(ms->pipes[index][1]);
		}
		else
			close(ms->pipes[index + position][1]);
	}
}

int	fds_valid(t_msl *ms, int index)
{
	if (ms->blocks[index]->fd_in < 0 || ms->blocks[index]->fd_out < 0)
		return (0);
	return (1);
}

void	exec_one(t_msl *ms, t_elem *arg)
{
	if (!fds_valid(ms, 0))
		ms->status = 1;
	if (arg)
		if (is_builtins(arg->name) && fds_valid(ms, 0))
			// if (ft_strmatch("export", arg->name) && arg->next != NULL)
				builtins_execution(ms, arg, 0);
	ms->pid[0] = fork();
	if (ms->pid[0] < 0)
		display_error_exec("minishell: ", "fork", 15);
	if (ms->pid[0] == 0)
	{
		if (ms->blocks[0]->is_input && fds_valid(ms, 0))
			handle_input(ms, 0, CHILD, 0);
		if (ms->blocks[0]->is_output && fds_valid(ms, 0))
			handle_output(ms, 0, CHILD, 0);
		if (is_builtins(arg->name) && fds_valid(ms, 0))
			builtins_execution(ms, arg, 1);
		if (!is_builtins(arg->name) && fds_valid(ms, 0))
			standard_execution(ms, arg);
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
		handle_input(ms, index, CHILD, -1);
		handle_output(ms, index, CHILD, -1);
		if (ms->blocks[index]->arg && fds_valid(ms, 0))
			distribute_cmd(ms, index);
		exit(ms->status);
	}
	else
	{
		close(ms->pipes[index - 1][1]);
		// close (ms->pipes[index][1]);		//segfault
		// handle_input(ms, index, PARENT, -1);
		// handle_output(ms, index, PARENT, -1);
	}
}

void	exec_middle_cmd(t_msl *ms, int index)
{
	ms->pid[index] = fork();
	if (ms->pid[index] < 0)
		display_error_exec("minishell: ", "fork", 15);
	else if (ms->pid[index] == 0)
	{
		// close(ms->pipes[index][0]);
		handle_input(ms, index, CHILD, -1);
		handle_output(ms, index, CHILD, 0);
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
		// close(ms->pipes[index][0]);
		handle_input(ms, index, CHILD, 0);
		handle_output(ms, index, CHILD, 0);
		// dup2(ms->pipes[index][1], STDOUT_FILENO);
		// close(ms->pipes[index][1]);

		// if (!ms->blocks[index]->arg->name)
		// {
		// 	exit(ms->status);
		// }

		// if (ms->blocks[index]->arg && ms->blocks[index]->fd_in >= 0)
		if (ms->blocks[index]->arg && fds_valid(ms, 0))
			distribute_cmd(ms, index);
		exit(ms->status);
	}
	else
	{
		handle_input(ms, index, PARENT, 0);
		handle_output(ms, index, PARENT, 0);
		// close(ms->pipes[index][1]);
	}
}

void	exec_pipe(t_msl *ms, int index, int mode)
{
	ms->pid[index] = fork();
	if (ms->pid[index] < 0)
		display_error_exec("minishell: ", "fork", 15);
	else if (ms->pid[index] == 0)
	{
		if (mode == FIRST)
		{
			handle_input(ms, index, CHILD, 0);
			handle_output(ms, index, CHILD, 0);
		}
		else if (mode == MID)
		{
			handle_input(ms, index, CHILD, -1);
			handle_output(ms, index, CHILD, 0);
		}
		else if (mode == LAST)
		{
			handle_input(ms, index, CHILD, -1);
			handle_output(ms, index, CHILD, -1);
		}
		if (ms->blocks[index]->arg && fds_valid(ms, index))
			distribute_cmd(ms, index);
		exit(ms->status);
	}
	else
	{
		if (mode == FIRST)
		{
			handle_input(ms, index, PARENT, 0);
			handle_output(ms, index, PARENT, 0);
		}
		else if (mode == MID)
		{
			handle_input(ms, index, PARENT, 2);
		}
		else if (mode == LAST)
		{
			handle_input(ms, index, PARENT, -1);
		}
	}
}

void	exec_cmd(t_msl *ms, int i)
{
	if (ms->c_cmd == 1)
		exec_one(ms, ms->blocks[i]->arg);
	else if (i == 0)
		// exec_first_cmd(ms, i);
		exec_pipe(ms, i, FIRST);
	else if (i == ms->c_cmd - 1)
		// exec_last_cmd(ms, i);
		exec_pipe(ms, i, LAST);
	else
		// exec_middle_cmd(ms, i);
		exec_pipe(ms, i, MID);
}
