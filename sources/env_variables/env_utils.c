/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:52:42 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/04/03 11:31:45 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**split_equal(char *env_var)
{
	char	**split_equal;
	int		i;
	int		len;
	int		len_two;

	len = 0;
	split_equal = ft_calloc(3, sizeof(char *));
	if (!split_equal)
		return (NULL);
	while (env_var[len] != '=')
		len++;
	split_equal[0] = ft_calloc(len + 1, sizeof(char));
	if (!split_equal[0])
		return (free(split_equal), NULL);
	i = -1;
	while (++i < len)
		split_equal[0][i] = env_var[i];
	len += 1;
	len_two = ft_strlen_null(env_var) - len;
	split_equal[1] = ft_calloc(len_two + 1, sizeof(char));
	if (!split_equal[0])
		return (free(split_equal[0]), free(split_equal), NULL);
	i = -1;
	while (++i < len_two)
		split_equal[1][i] = env_var[i + len];
	return (split_equal);
}

void	display_env(t_msl *ms, int mode)
{
	t_var	*vars;
	int		i;

	i = -1;
	if (mode == 0)
	{
		if (ms->arrenv)
		{
			while (ms->arrenv[++i])
				printf("%s\n", ms->arrenv[i]);
		}
		printf("_=/usr/bin/env\n");
	}
	else if (mode == 1 && ms->arrexport)
	{
		while (ms->arrexport[++i])
			printf("declare -x %s\n", ms->arrexport[i]);
	}
}

int	envsize(t_msl *ms, int mode)
{
	int		envsize;
	t_var	*tmp_env;

	envsize = 0;
	tmp_env = ms->env;
	while (tmp_env != NULL)
	{
		if (mode == 0 && tmp_env->in_env)
			envsize++;
		else if (mode == 1)
			envsize++;
		tmp_env = tmp_env->next;
	}
	return (envsize);
}
