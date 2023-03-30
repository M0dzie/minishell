/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:40:43 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/03/30 23:34:50 by mehdisapin       ###   ########.fr       */
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

// void	var_add_back(t_msl *ms, t_var *var)
// {
// 	t_var	*add_back;

// 	if (!ms->env->name)
// 		ms->env = var;
// 	// if (!ms->env)
// 	// 	ms->env = var;
// 	else
// 	{
// 		add_back = ms->env;
// 		while (add_back->next != NULL)
// 			add_back = add_back->next;
// 		add_back->next = var;
// 	}
// }

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

t_var	*init_nullenv(t_msl *ms)
{
	t_var	*env_stack;

	var_add_back(&env_stack, new_var("PWD", ms->pwd, 1));
	var_add_back(&env_stack, new_var("SHLVL", "1", 1));
	var_add_back(&env_stack, new_var("OLDPWD", NULL, 0));
	return (env_stack);
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

t_var	*new_varenv(char *env, int in_env)
{
	t_var	*new_var;
	int		i;
	int		j;

	new_var = ft_calloc(1, sizeof(t_var));
	if (!new_var)
		return (NULL);
	new_var->name = ft_calloc(len_env(env, BEFORE) + 1, sizeof(char));
	if (!new_var->name)
		return (free(new_var), NULL);
	i = -1;
	while (env[++i] && env[i] != '=')
		new_var->name[i] = env[i];
	if (env[i] == '=')
		i++;
	new_var->value = ft_calloc(len_env(env, AFTER) + 1, sizeof(char));
	if (!new_var->value)
		return (free(new_var->name), free(new_var), NULL);
	j = -1;
	while (env[++j + i])
		new_var->value[j] = env[j + i];
	new_var->in_env = in_env;
	new_var->next = NULL;
	return (new_var);
}

t_var	*gen_env(char **envp)
{
	t_var	*env_stack;
	int		i;

	env_stack = NULL;
	i = -1;
	while (envp[++i])
	{
		if (!is_underscore(envp[i]))
		{
			if (ft_strncmp(envp[i], "SHLVL", 5) == 0)
			{
				// printf("SHLVL found : %s\n", envp[i]);
			}
			else
			{
				// printf("%s\n", envp[i]);
				var_add_back(&env_stack, new_varenv(envp[i], 1));
				// printf("%s\n", env_stack->name);
			}
		}
	}
	return (env_stack);
}

void	init_env(t_msl *ms, char **envp)
{
	// char	**tmp_split;
	int		i;
	char	bufpwd[BUFSIZ];
	char	*tmp_increm;

	i = -1;
	// tmp_split = NULL;
	ms->pwd = getcwd(bufpwd, BUFSIZ);
	// ms->env = ft_calloc(1, sizeof(t_var *));
	if (!envp[0])
		init_nullenv(ms);
	else
		ms->env = gen_env(envp);

	// printf("first var name %s value %s\n", ms->env->name, ms->env->value);
	
	ms->arrenv = ft_getenv(ms);
	// printf("%s\n", ms->arrenv[0]);
	// free_env(ms);
	// printf("first var name %s value %s\n", ms->env->name, ms->env->value);
	ms->arrexport = ft_getexport(ms);
}
