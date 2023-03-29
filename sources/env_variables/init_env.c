/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:40:43 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/03/29 17:59:25 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	var_add_back(t_msl *ms, t_var *var)
{
	t_var	*add_back;

	if (!ms->env->name)
		ms->env = var;
	else
	{
		add_back = ms->env;
		while (add_back->next != NULL)
			add_back = add_back->next;
		add_back->next = var;
	}
}

t_var	*new_var(char *name, char *value, int in_env)
{
	t_var	*new_var;

	new_var = ft_calloc(1, sizeof(t_var));
	if (!new_var)
		return (NULL);
	new_var->name = name;
	new_var->value = value;
	new_var->in_env = in_env;
	new_var->next = NULL;
	return (new_var);
}

void	init_nullenv(t_msl *ms)
{
	var_add_back(ms, new_var("PWD", ms->pwd, 1));
	var_add_back(ms, new_var("SHLVL", "1", 1));
	var_add_back(ms, new_var("OLDPWD", NULL, 0));
}

void	init_env(t_msl *ms, char **envp)
{
	char	**tmp_split;
	int		i;
	char	bufpwd[BUFSIZ];

	i = -1;
	tmp_split = NULL;
	ms->pwd = getcwd(bufpwd, BUFSIZ);
	ms->env = ft_calloc(ft_arrlen(envp) + 1, sizeof(t_var *));
	if (!envp[0])
		init_nullenv(ms);
	while (envp[++i])
	{
		tmp_split = split_equal(envp[i]);
		if (!ft_strmatch(tmp_split[0], "_"))
		{
			if (ft_strmatch(tmp_split[0], "SHLVL"))
				tmp_split[1] = ft_itoa(ft_atoi(tmp_split[1]) + 1);
			// var_add_back(ms, new_var(ft_strdup_null(tmp_split[0]), ft_strdup_null(tmp_split[1]), 1));
			var_add_back(ms, new_var(tmp_split[0], tmp_split[1], 1));
		}
		// ft_arrfree(tmp_split);
	}
	// free(ms->env);
	ms->arrenv = ft_getenv(ms);
	ms->arrexport = ft_getexport(ms);
}
