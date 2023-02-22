/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:07:13 by msapin            #+#    #+#             */
/*   Updated: 2023/02/22 12:06:24 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_env(t_var **stack, char **envp)		// need cleanup of unused envp
{
	t_var	*vars;
	int		i = 0;

	if (!(*stack))
		return ;
	else
	{
		vars = (*stack);
		while (vars != NULL)
		{
			// printf("%s\n", envp[i]);
			printf("%s=%s\n", vars->name, vars->value);
			vars = vars->next;
			i++;
		}
	}
}

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
	t_var	*env_vars;

	// add protection if not envp

	i = -1;
	while (envp[++i])
	{
		tmp_split = split_equal(envp[i]);
		var_add_back(&env_vars, new_var(tmp_split[0], tmp_split[1]));
	}
	if (tmp_split)
		ft_arrfree(tmp_split);
	display_env(&env_vars, envp);
}
