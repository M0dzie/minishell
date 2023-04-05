/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:01:57 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/04/04 21:22:14 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*getexport_var(char *name, char *value)
{
	char	*str_var;
	int		varlen;
	int		i;
	int		j;

	varlen = ft_strlen_null(name) + ft_strlen_null(value) + 3;
	str_var = ft_calloc(varlen + 1, sizeof(char));
	if (!str_var)
		return (display_error_exec("minishell: ", "getenv_var: ", 6), NULL);
	i = -1;
	while (name[++i])
		str_var[i] = name[i];
	if (value)
	{
		str_var[i] = '=';
		str_var[++i] = '"';
		i += 1;
		j = -1;
		while (value[++j])
			str_var[i + j] = value[j];
		str_var[i + j] = '"';
	}
	return (str_var);
}

int	len_until_eq(char *s1, char *s2)
{
	int	len_s1;
	int	len_s2;

	len_s1 = 0;
	len_s2 = 0;
	while (s1[len_s1] && s1[len_s1] != '=')
		len_s1++;
	while (s2[len_s2] && s2[len_s2] != '=')
		len_s2++;
	if (len_s1 > len_s2)
		return (len_s1);
	if (len_s1 < len_s2)
		return (len_s2);
	return (len_s1);
}

int	varcmp(char *s1, char *s2)
{
	size_t	i;
	int		return_value;
	int		len_biggest;

	i = 0;
	return_value = 0;
	len_biggest = len_until_eq(s1, s2);
	while (i < len_biggest)
	{
		if ((s1[i] == '=' || !s1[i]) && s2[i])
			return (-(int)s2[i]);
		else if ((s2[i] == '=' || !s2[i]) && s1[i])
			return ((int)s1[i]);
		else if (s1[i] != s2[i])
		{
			return_value = s1[i] - s2[i];
			return (return_value);
		}
		i++;
	}
	return (0);
}

char	**get_tmpenv(t_msl *ms)
{
	t_var	*tmp_env;
	char	**arrenv;
	int		i;

	if (!ms->env)
		return (NULL);
	arrenv = ft_calloc(envsize(ms, EXPORT) + 1, sizeof(char *));
	if (!arrenv)
		return (display_error_exec("minishell: ", "arrenv: ", 6), NULL);
	tmp_env = ms->env;
	i = -1;
	while (tmp_env != NULL)
	{
		arrenv[++i] = getexport_var(tmp_env->name, tmp_env->value);
		tmp_env = tmp_env->next;
	}
	return (arrenv);
}

char	**ft_getexport(t_msl *ms)
{
	int		i;
	int		j;
	int		index;
	char	**arrenv;
	char	**getexport;

	if (!ms->env)
		return (NULL);
	arrenv = get_tmpenv(ms);
	if (!arrenv)
		return (NULL);
	getexport = ft_calloc(envsize(ms, EXPORT) + 1, sizeof(char *));
	if (!getexport)
		return (display_error_exec("minishell: ", "getexport: ", 6), NULL);
	i = -1;
	while (arrenv[++i])
	{
		index = 0;
		j = -1;
		while (arrenv[++j])
			if (varcmp(arrenv[i], arrenv[j]) > 0)
				index++;
		getexport[index] = ft_strdup_null(arrenv[i]);
	}
	return (ft_arrfree(arrenv), getexport);
}
