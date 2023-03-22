/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:01:19 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/03/22 21:07:57 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_var	*getvar(t_msl *ms, char *name)
{
	t_var	*tmp_stack;

	// ft_putstr_fd("error getvar\n", 2);
	if (ms->env->name)
	{
		tmp_stack = ms->env;
		while (tmp_stack != NULL)
		{
			// ft_putstr_fd("return null\n", 2);
			if (ft_strmatch(tmp_stack->name, name))
			// {
				return (tmp_stack);
			// }
			tmp_stack = tmp_stack->next;
		}
	}
	// ft_putstr_fd("return null end\n", 2);
	return (NULL);
}

char	*getenv_var(char *name, char *value)
{
	char	*str_var;
	int		varlen;
	int		i;
	int		j;

	varlen = ft_strlen_null(name) + ft_strlen_null(value) + 1;
	str_var = ft_calloc(varlen + 1, sizeof(char));
	if (!str_var)
		return (display_error_exec("bash: ", "getenv_var: ", 6), NULL);
	i = -1;
	while (name[++i])
		str_var[i] = name[i];
	if (!value)
		return (str_var);
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
	char	**getenv;
	int		nb_var;
	int		i;

	nb_var = envsize(ms, ENV);
	getenv = ft_calloc(nb_var + 1, sizeof(char *));
	if (!getenv)
		return (display_error_exec("bash: ", "ms->env: ", 6), NULL);
	if (!ms->env->name)
		return (NULL);
	tmp_env = ms->env;
	i = -1;
	while (tmp_env != NULL)
	{
		if (tmp_env->in_env)
			getenv[++i] = getenv_var(tmp_env->name, tmp_env->value);
		tmp_env = tmp_env->next;
	}
	return (getenv);
}

// char	**ft_getenv(t_msl *ms, int mode)
// {
// 	t_var	*tmp_env;
// 	char	**getenv;
// 	int		nb_var;
// 	int		i;

// 	nb_var = envsize(ms, mode);
// 	getenv = ft_calloc(nb_var + 1, sizeof(char *));
// 	if (!getenv)
// 		return (display_error_exec("bash: ", "ms->env: ", 6), NULL);
// 	// if (nb_var == 0)
// 	// 	return (display_error_exec("bash: ", "getenv: ", 8), NULL);
// 	// printf("envsize %d\n", nb_var);
// 	tmp_env = ms->env;
// 	if (!ms->env->name)
// 		return (NULL);
// 	i = -1;
// 	while (tmp_env != NULL)
// 	{
// 		// printf("declenchement %s\n", tmp_env->name);
// 		if (mode == 0 && tmp_env->in_env)
// 			getenv[++i] = getenv_var(tmp_env->name, tmp_env->value);
// 		else if (mode == 1)
// 			getenv[++i] = getexport_var(tmp_env->name, tmp_env->value);
// 		tmp_env = tmp_env->next;
// 	}
// 	return (getenv);
// }
