/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:07:13 by msapin            #+#    #+#             */
/*   Updated: 2023/02/23 14:04:47 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minimehdi.h"

t_var	*getvar(t_msl *ms, char *name)
{
	t_var	*tmp_stack;

	tmp_stack = ms->env;
	while (tmp_stack != NULL)
	{
		if (strict_cmp(tmp_stack->name, name))
			return (tmp_stack);
		tmp_stack = tmp_stack->next;
	}
	return (NULL);
}

int	envsize(t_msl *ms)
{
	int		envsize;
	t_var	*tmp_env;

	envsize = 0;
	tmp_env = ms->env;
	while (tmp_env != NULL)
	{
		envsize++;
		tmp_env = tmp_env->next;
	}
	return (envsize);
}

char	*getenv_var(char *name, char *value)
{
	char 	*str_var;
	int		varlen;
	int		i;
	int		j;

	varlen = ft_strlen(name) + ft_strlen(value) + 1;
	str_var = ft_calloc(varlen + 1, sizeof(char));
	if (!str_var)
		return (display_error_exec("bash: ", "getenv_var: ", 6), NULL);
	i = -1;
	while (name[++i])
		str_var[i] = name[i];
	str_var[i] = '=';
	i += 1;
	j = -1;
	while (value[++j])
		str_var[i + j] = value[j];
	return (str_var);
}

char	**ft_getenv(t_msl *ms)
{
	t_var	*tmp_env;
	char 	**getenv;
	int		nb_var;
	int		i;

	nb_var = envsize(ms);
	getenv = ft_calloc(nb_var, sizeof(char *));
	if (!getenv)
		return (display_error_exec("bash: ", "ms->env: ", 6), NULL);
	if (nb_var == 0)
		return (display_error_exec("bash: ", "getenv: ", 8), NULL);
	tmp_env = ms->env;
	i = 0;
	while (tmp_env != NULL)
	{
		getenv[i] = getenv_var(tmp_env->name, tmp_env->value);
		tmp_env = tmp_env->next;
		i++;
	}
	return (getenv);
}

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
	while (envp[++i])
	// while (i++ < 5)
	{
		tmp_split = split_equal(envp[i]);
		var_add_back(ms, new_var(tmp_split[0], tmp_split[1]));
	}
}
