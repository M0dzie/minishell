/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:43:24 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/04/03 21:43:32 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	invalid_first(char *name)
{
	char	*invalid_char;
	int		i;

	if (!name[0])
		return (1);
	invalid_char = "1234567890=";
	i = -1;
	while (invalid_char[++i])
	{
		if (invalid_char[i] == name[0])
			return (1);
	}
	return (0);
}

int	invalid_option(char *name)
{
	char	*invalid_opt;
	int		i;
	int		namelen;

	namelen = ft_strlen(name);
	if (name[0] == '-' && namelen > 1)
	{
		invalid_opt = ft_calloc(3, sizeof(char));
		if (!invalid_opt)
			return (display_error_exec("minishell: ", "getenv_var: ", 6), 1);
		invalid_opt[0] = name[0];
		invalid_opt[1] = name[1];
		return (display_error_exec("minishell: export: ", invalid_opt, 1), 1);
	}
	return (0);
}

int	invalid_identifier(char *name)
{
	char	*invalid_char;
	int		i;
	int		j;

	if (invalid_first(name))
		return (display_error_exec("minishell: export: '", name, 14), 1);
	else if (invalid_option(name))
		return (2);
	invalid_char = "`~!@#$%^&*-+.,\\?:{}[]";
	i = 0;
	while (name[i] && name[i] != '=')
	{
		j = -1;
		while (invalid_char[++j])
		{
			if (name[i] == invalid_char[j])
				return (display_error_exec("minishell: export: '", name, 14), 1);
		}
		i++;
	}
	return (0);
}

void	update_varenv(t_var *tmp_var, char *value)
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

t_var	*fill_emptyenv(t_msl *ms, t_var **env, char *args_cmd)		// remove env and return void
{
	t_var	*env_stack;
	char	**tmp_split;
	int		i;
	int		j;

	env_stack = NULL;

	if (ft_strchr(args_cmd, '='))
	{
		var_add_back(&ms->env, new_varenv(args_cmd, 1));	// fix
	}
	else
	{
		var_add_back(&ms->env, new_var(ft_strdup_null(args_cmd), NULL, 0));
	}

	return (env_stack);
}

void	var_handling(t_msl *ms, char *args_cmd)
{
	t_var	*tmp_var;
	char	**tmp_split;

	// if (ms->env->name == NULL)
	if (ms->env == NULL)
	{
		printf("env empty\n");
		// free(ms->env);
		// ms->env = fill_emptyenv(ms, args_cmd);
		// ms->env = fill_emptyenv(ms, &ms->env, args_cmd);
		fill_emptyenv(ms, &ms->env, args_cmd);

		printf("env name %s\n", ms->env->name);
		// fill_emptyenv(ms, args_cmd);
	}
	else if (ft_strchr(args_cmd, '='))
	{
		tmp_split = split_equal(args_cmd);
		tmp_var = getvar(ms, tmp_split[0]);
		if (tmp_var)
		{
			// update_varenv(tmp_var, args_cmd);
			free(tmp_var->value);
			tmp_var->value = ft_strdup_null(tmp_split[1]);
			tmp_var->in_env = 1;
		}
		else
			var_add_back(&ms->env, new_varenv((args_cmd), 1));	// fix
		ft_arrfree(tmp_split);
	}
	else
	{
		tmp_var = getvar(ms, args_cmd);
		if (!tmp_var)
			var_add_back(&ms->env, new_var(ft_strdup_null(args_cmd), NULL, 0));	// fix
	}
	if (ms->arrenv)
		ft_arrfree(ms->arrenv);
	if (ms->arrexport)
		ft_arrfree(ms->arrexport);
	ms->arrenv = ft_getenv(ms);
	ms->arrexport = ft_getexport(ms);
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
