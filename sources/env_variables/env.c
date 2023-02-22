/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:07:13 by msapin            #+#    #+#             */
/*   Updated: 2023/02/22 17:45:46 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_env(t_msl *ms)
{
	t_var	*vars;

	if (!ms->env)
		return ;
	vars = ms->env;
	while (vars != NULL)
	{
		printf("%s=%s\n", vars->name, vars->value);
		vars = vars->next;
	}
}

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

t_var	*new_var(char *name, char *value)
{
	t_var	*new_var;

	new_var = ft_calloc(1, sizeof(t_var));
	if (!new_var)
		return (NULL);
	new_var->name = name;
	new_var->value = value;
	new_var->next = NULL;
	return (new_var);
}

char	**split_equal(char *env_var)
{
	char	**split_equal;
	int		i;
	int		len;
	int		len_two;

	len = 0;
	split_equal = ft_calloc(3, sizeof(char *));
	while (env_var[len] != '=')
		len++;
	split_equal[0] = ft_calloc(len + 1, sizeof(char));
	i = -1;
	while (++i < len)
		split_equal[0][i] = env_var[i];
	len += 1;
	len_two = ft_strlen(env_var) - len;
	split_equal[1] = ft_calloc(len_two + 1, sizeof(char));
	i = -1;
	while (++i < len_two)
		split_equal[1][i] = env_var[i + len];
	return (split_equal);
}

void	init_env(t_msl *ms, char **envp)
{
	char	**tmp_split;
	int		i;

	i = -1;
	ms->env = ft_calloc(ft_arrlen(envp), sizeof(char *));
	if (!ms->env)
	{
		display_error_exec("bash: ", "ms->env: ", 6);
		return ;
	}
	// while (envp[++i])
	while (i++ < 5)
	{
		tmp_split = split_equal(envp[i]);
		var_add_back(ms, new_var(tmp_split[0], tmp_split[1]));
	}
}
