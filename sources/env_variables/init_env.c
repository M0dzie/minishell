/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 11:40:43 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/04/04 21:22:39 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	cpyint(char	*char_int, int n, size_t len)
{
	unsigned int	unsign_n;
	size_t			sign;

	if (n == 0)
		char_int[0] = '0';
	unsign_n = (unsigned int)n;
	sign = 0;
	while (len > sign)
	{
		char_int[len - 1] = (unsign_n % 10) + 48;
		unsign_n = unsign_n / 10;
		len--;
	}
}

t_var	*new_varlvl(char *env, int in_env)
{
	t_var	*new_var;
	int		i;
	int		j;
	int		shlvl;

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
	shlvl = ft_atoi(env + i) + 1;
	new_var->value = ft_calloc(ft_intlen(shlvl) + 1, sizeof(char));
	if (!new_var->value)
		return (free(new_var->name), free(new_var), NULL);
	cpyint(new_var->value, shlvl, ft_intlen(shlvl));
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
				var_add_back(&env_stack, new_varlvl(envp[i], 1));
			else
				var_add_back(&env_stack, new_varenv(envp[i], 1));
		}
	}
	return (env_stack);
}

void	init_env(t_msl *ms, char **envp)
{
	char	bufpwd[BUFSIZ];

	ms->env = gen_env(envp);
	if (!getvar(ms, "PWD"))
		var_add_back(&ms->env, new_var(ft_strdup("PWD"),
				ft_strdup(getcwd(bufpwd, BUFSIZ)), 1));
	if (!getvar(ms, "SHLVL"))
		var_add_back(&ms->env, new_var(ft_strdup("SHLVL"), ft_strdup("1"),
				1));
	if (!getvar(ms, "OLDPWD"))
		var_add_back(&ms->env, new_var(ft_strdup("OLDPWD"), NULL, 0));
	ms->arrenv = ft_getenv(ms);
	ms->arrexport = ft_getexport(ms);
}
