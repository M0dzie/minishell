/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:01:57 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/03/22 19:50:44 by mehdisapin       ###   ########.fr       */
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
		return (display_error_exec("bash: ", "getenv_var: ", 6), NULL);
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
	printf("-----%s\n", str_var);
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

char	**ft_getexport(t_msl *ms)
{
	int		i;
	int		j;
	int		index;
	char	**arr_export;
	char	**getexport;

	i = -1;
	getexport = ft_calloc(envsize(ms, EXPORT) + 1, sizeof(char *));
	arr_export = ft_getenv(ms);
	// printf("ft_getexport %d %s\n",envsize(ms, EXPORT), arr_export[0]);
	// if (!arr_export)
	// 	return (NULL);
	ft_putarr_fd(ms->arrenv, 1);
	// while (arr_export[++i])
	// {
	// 	index = 0;
	// 	j = -1;
	// 	printf("%s\n", arr_export[i]);
	// 	while (arr_export[++j])
	// 	{
	// 		if (varcmp(arr_export[i], arr_export[j]) > 0)
	// 			index++;
	// 	}
	// 	getexport[index] = ft_strdup_null(arr_export[i]);
	// }
	// ft_arrfree(arr_export);
	return (getexport);
}
