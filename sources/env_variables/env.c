/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:07:13 by msapin            #+#    #+#             */
/*   Updated: 2023/02/21 18:48:10 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_env(t_var **stack)
{
	t_var	*vars;

	if (!(*stack))
		return ;
	else
	{
		vars = (*stack);
		while (vars != NULL)
		{
			printf("%s=%s\n", vars->name, vars->value);
			vars = vars->next;
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

	// split_equal
	len = 0;
	split_equal = ft_calloc(3, sizeof(char *));
	while (env_var[len] != '=')
		len++;
	split_equal[0] = ft_calloc(len, sizeof(char));
	i = -1;
	while (++i < len)
		split_equal[0][i] = env_var[i];
	len + 1;
	len_two = ft_strlen(env_var) - len;
	split_equal[1] = ft_calloc(len_two, sizeof(char));
	i = -1;
	while (++i < len_two)
		split_equal[1][i] = env_var[i + len];
	// printf("len end line : %d\n", len_two);
	return (split_equal);
}

void	init_env(t_msl *ms, char **envp)
{
	char	**tmp_split;
	int		i;
	t_var	*env_vars;

	i = -1;
	while (envp[++i])
	// while (++i < 1)
	{
		tmp_split = split_equal(envp[i]);
		// printf("%s = %s\n", tmp_split[0], tmp_split[1]);
		var_add_back(&env_vars, new_var(tmp_split[0], tmp_split[1]));
		// printf("VAR NAME : %s\n", tmp_split[0]);
		// printf("VALUE : %s\n\n", tmp_split[1]);
	}
	display_env(&env_vars);
}
