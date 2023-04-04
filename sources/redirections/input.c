/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:43:28 by msapin            #+#    #+#             */
/*   Updated: 2023/04/04 17:49:04 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_input(t_msl *ms, t_block *block)
{
	t_elem	*tmp_arg;
	int		heredoc;

	heredoc = is_heredoc(block);
	get_heredoc(ms, block, heredoc);
	if (block->in)
	{
		tmp_arg = block->in;
		while (tmp_arg != NULL)
		{
			if (block->fd_in)
				close (block->fd_in);
			if (tmp_arg->type == INPUT)
			{
				block->fd_in = open(tmp_arg->name, O_RDONLY);
				if (block->fd_in < 0)
					return (display_error_exec("minishell: ", tmp_arg->name, 2), 1);
			}
			tmp_arg = tmp_arg->next;
		}
		if (heredoc == 2)
			block->is_input = HEREDOC;
		else
			block->is_input = INPUT;
	}
}
