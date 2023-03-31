/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:43:51 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/03/31 15:54:23 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env(t_msl *ms)
{
	t_var	*tmp_env;

	while (ms->env != NULL)
	{
		tmp_env = ms->env;
		ms->env = ms->env->next;
		if (tmp_env->name)
			free(tmp_env->name);
		if (tmp_env->value)
			free(tmp_env->value);
		free(tmp_env);
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
			freelist_elem(ms->blocks[i]->arg);
		if (ms->blocks[i]->in)
			freelist_elem(ms->blocks[i]->in);
		if (ms->blocks[i]->out)
			freelist_elem(ms->blocks[i]->out);
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
	if (ms->input)
		free(ms->input);
	rl_clear_history();
	free_env(ms);
	ft_arrfree(ms->arrenv);
	ft_arrfree(ms->arrexport);
	close(0);
	close(1);
	close(2);
}
