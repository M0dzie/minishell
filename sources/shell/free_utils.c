/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 02:09:40 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/04/05 02:11:11 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env(t_msl *ms)
{
	t_var	*tmp_env;
	t_var	*next;

	tmp_env = ms->env;
	while (tmp_env != NULL)
	{
		next = tmp_env->next;
		if (tmp_env->name)
			free(tmp_env->name);
		if (tmp_env->value)
			free(tmp_env->value);
		free(tmp_env);
		tmp_env = next;
	}
}
