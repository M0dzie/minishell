/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:17:30 by msapin            #+#    #+#             */
/*   Updated: 2023/04/04 16:20:00 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_varenv(t_var *tmp_var, char *value)
{
	int	i;
	int	j;

	if (!tmp_var)
		return ;
	if (tmp_var->value)
		free(tmp_var->value);
	tmp_var->value = ft_calloc(len_env(value, AFTER) + 1, sizeof(char));
	if (!tmp_var->value)
	{
		display_error_exec("minishell: ", "tmp_var->value", 15);
		return ;
	}
	i = 0;
	if (ft_strchr(value, '='))
	{
		while (value[i] && value[i] != '=')
			i++;
		if (value[i] == '=')
			i++;
	}
	j = -1;
	while (value[++j + i])
		tmp_var->value[j] = value[j + i];
	tmp_var->in_env = 1;
}

static void	fill_emptyenv(t_msl *ms, char *args_cmd)
{
	if (ft_strchr(args_cmd, '='))
		var_add_back(&ms->env, new_varenv(args_cmd, 1));
	else
		var_add_back(&ms->env, new_var(ft_strdup_null(args_cmd), NULL, 0));
}

static void	var_handling(t_msl *ms, char *args_cmd)
{
	t_var	*tmp_var;
	char	**tmp_split;

	if (ms->env == NULL)
		fill_emptyenv(ms, args_cmd);
	else if (ft_strchr(args_cmd, '='))
	{
		tmp_split = split_equal(args_cmd);
		tmp_var = getvar(ms, tmp_split[0]);
		if (tmp_var)
		{
			free(tmp_var->value);
			tmp_var->value = ft_strdup_null(tmp_split[1]);
			tmp_var->in_env = 1;
		}
		else
			var_add_back(&ms->env, new_varenv((args_cmd), 1));
		ft_arrfree(tmp_split);
	}
	else if (!getvar(ms, args_cmd))
		var_add_back(&ms->env, new_var(ft_strdup_null(args_cmd), NULL, 0));
	update_arr(ms);
}

int	exec_export(t_msl *ms, char **args_cmd)
{
	int		i;
	int		exit_stat;
	int		tmp_exit;

	i = 0;
	exit_stat = 0;
	tmp_exit = 0;
	if (ft_arrlen(args_cmd) == 1)
		display_env(ms, EXPORT);
	while (args_cmd[++i])
	{
		tmp_exit = invalid_identifier(args_cmd[i]);
		if (tmp_exit == 0 && ms->c_pipe == 0)
			var_handling(ms, args_cmd[i]);
		else
			exit_stat = tmp_exit;
	}
	return (exit_stat);
}
