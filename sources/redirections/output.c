/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:44:12 by msapin            #+#    #+#             */
/*   Updated: 2023/04/05 00:52:50 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	display_error_output(t_elem *tmp_file)
{
	if (tmp_file->name[ft_strlen_null(tmp_file->name) - 1] == '/')
		return (display_error_exec("minishell: ", tmp_file->name, 18), 1);
	else if (tmp_file->name[0] == '/')
		return (display_error_exec("minishell: ", tmp_file->name, 13), 1);
	else if (ft_strchr(tmp_file->name, '/') == 0)
		return (display_error_exec("minishell: ", tmp_file->name, 13), 1);
	else
		return (display_error_exec("minishell: ", tmp_file->name, 2), 1);
}

int	check_output(t_msl *ms, t_block *block)
{
	t_elem	*tmp_file;

	tmp_file = block->out;
	while (tmp_file != NULL)
	{
		if (tmp_file->type == TRUNC)
			block->fd_out = open(tmp_file->name, O_CREAT | O_RDWR | O_TRUNC,
					0664);
		if (tmp_file->type == APPEND)
			block->fd_out = open(tmp_file->name, O_CREAT | O_RDWR | O_APPEND,
					0664);
		if (block->fd_out < 0)
			return (display_error_output(tmp_file));
		tmp_file = tmp_file->next;
	}
	block->is_output = 1;
	return (0);
}
