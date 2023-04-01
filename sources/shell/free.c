/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:43:51 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/04/01 16:06:19 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env(t_msl *ms)
{
	t_var	*tmp_env;
	t_var	*next;

	tmp_env = ms->env;
	while (tmp_env != NULL)
	{
		next = tmp_env->next;
		free(tmp_env->name);
		if (tmp_env->in_env)
			free(tmp_env->value);
		free(tmp_env);
		tmp_env = next;
	}
}

void	freelist_elem(t_elem *elem)
{
	t_elem	*tmp_elem;

	while (elem != NULL)
	{
		tmp_elem = elem;
		elem = elem->next;
		free(tmp_elem->name);
		free(tmp_elem);
	}
}

void	arrint_free(t_msl *ms)
{
	int	i;

	i = -1;
	while (++i < ms->c_pipe)
	{
		close(ms->pipes[i][0]);
		close(ms->pipes[i][1]);
		free(ms->pipes[i]);
	}
	free(ms->pipes);
}

void	free_exec(t_msl *ms)
{
	t_block	*tmp_block;
	int		i;

	i = 0;
	while (ms->blocks[i])
	{
		if (ms->blocks[i]->arg)
		{
			freelist_elem(ms->blocks[i]->arg);
			ft_arrfree(ms->blocks[i]->args_cmd);
		}
		if (ms->blocks[i]->in)
		{
			close(ms->blocks[i]->fd_in);
			freelist_elem(ms->blocks[i]->in);
		}
		if (ms->blocks[i]->out)
		{
			close(ms->blocks[i]->fd_out);
			freelist_elem(ms->blocks[i]->out);
		}
		if (ms->blocks[i]->input)
			free(ms->blocks[i]->input);
		free(ms->blocks[i]);
		i++;
	}
	free(ms->blocks);
	free(ms->pid);
	arrint_free(ms);
}

void	free_blocks(t_msl *ms)
{

}

void	free_global(t_msl *ms)
{
	free_env(ms);
	// if (ms->input)
	// 	free(ms->input);
	rl_clear_history();
	ft_arrfree(ms->arrenv);
	ft_arrfree(ms->arrexport);
	close(0);
	close(1);
	close(2);
}
