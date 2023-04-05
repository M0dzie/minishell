/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 23:21:56 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/04/05 00:58:48 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	dupclose(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}

void	dupheredoc(t_msl *ms, int index)
{
	int	tmp_pipe[2];

	pipe(tmp_pipe);
	dup2(tmp_pipe[0], 0);
	write(tmp_pipe[1], ms->blocks[index]->input,
		ft_strlen_null(ms->blocks[index]->input));
	free(ms->blocks[index]->input);
	close(tmp_pipe[1]);
}

void	handle_output(t_msl *ms, int index, int position)
{
	if (ms->blocks[index]->is_output)
		dupclose(ms->blocks[index]->fd_out, STDOUT_FILENO);
	else
		dup2(ms->pipes[index + position][1], STDOUT_FILENO);
}

void	handle_input(t_msl *ms, int index, int position)
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
