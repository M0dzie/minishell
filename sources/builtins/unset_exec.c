/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:51:59 by msapin            #+#    #+#             */
/*   Updated: 2023/04/04 14:55:25 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	switch_tmp_var(t_var *var, t_var *tmp, t_var *src)
{
	free(var->name);
	free(var->value);
	free(var);
	tmp->next = src;
}

static void	switch_ms_var(t_var *var, t_msl *ms, t_var *src)
{
	free(var->name);
	free(var->value);
	free(var);
	ms->env = src;
}

static t_var	*get_previous_var(t_msl *ms, char *var_name)
{
	t_var	*prev;

	prev = ms->env;
	while (prev->next != NULL)
	{
		if (ft_strmatch(prev->next->name, var_name))
			return (prev);
		prev = prev->next;
	}
	prev = NULL;
	return (prev);
}

static void	unset_handling(t_msl *ms, char *var_name)
{
	t_var	*tmp_var;
	t_var	*tmp_prev;
	t_var	*tmp_next;

	tmp_var = getvar(ms, var_name);
	if (tmp_var)
	{
		tmp_prev = get_previous_var(ms, var_name);
		tmp_next = tmp_var->next;
		if (tmp_next == NULL && tmp_prev)
			switch_tmp_var(tmp_var, tmp_prev, NULL);
		else if (tmp_prev == NULL && tmp_next)
			switch_ms_var(tmp_var, ms, tmp_next);
		else if (tmp_next == NULL && tmp_prev == NULL)
			switch_ms_var(tmp_var, ms, NULL);
		else
			switch_tmp_var(tmp_var, tmp_prev, tmp_next);
		update_arr(ms);
	}
}

int	exec_unset(t_msl *ms, char **args_cmd)
{
	int		i;
	int		valid;
	int		rtn;

	i = 0;
	rtn = 0;
	while (args_cmd[++i])
	{
		valid = invalid_identifier_unset(args_cmd[i]);
		if (valid == 0 && ms->c_pipe == 0)
			unset_handling(ms, args_cmd[i]);
		else
			rtn = valid;
	}
	return (rtn);
}
