/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:47:51 by msapin            #+#    #+#             */
/*   Updated: 2023/04/04 18:53:31 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	var_add_back(t_var **stack, t_var *var)
{
	t_var	*add_back;

	if (!(*stack))
		(*stack) = var;
	else
	{
		add_back = (*stack);
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

int	is_underscore(char *var_env)
{
	if (!var_env || !var_env[1])
		return (0);
	if (var_env[0] == '_' && var_env[1] == '=')
		return (1);
	return (0);
}

int	len_env(char *env, int mode)
{
	int	len_before;
	int	len_after;

	if (!env)
		return (0);
	len_before = 0;
	if (mode == BEFORE)
	{
		while (env[len_before] && env[len_before] != '=')
			len_before++;
		return (len_before);
	}
	else
	{
		len_after = 0;
		while (env[len_before] && env[len_before] != '=')
			len_before++;
		if (env[len_before + len_after] == '=')
			len_before++;
		while (env[len_before + len_after])
			len_after++;
		return (len_after);
	}
	return (0);
}
