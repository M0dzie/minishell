/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:07:13 by msapin            #+#    #+#             */
/*   Updated: 2023/02/25 20:11:20 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minimehdi.h"

t_var	*getvar(t_msl *ms, char *name)
{
	t_var	*tmp_stack;

	if (ms->env->name)
	{
		tmp_stack = ms->env;
		while (tmp_stack != NULL)
		{
			if (strict_cmp(tmp_stack->name, name))
				return (tmp_stack);
			tmp_stack = tmp_stack->next;
		}
	}
	return (NULL);
}

int	envsize(t_msl *ms)
{
	int		envsize;
	t_var	*tmp_env;

	envsize = 0;
	tmp_env = ms->env;
	while (tmp_env != NULL)
	{
		envsize++;
		tmp_env = tmp_env->next;
	}
	return (envsize);
}

char	*getenv_var(char *name, char *value)
{
	char 	*str_var;
	int		varlen;
	int		i;
	int		j;

	varlen = ft_strlen(name) + ft_strlen(value) + 1;
	str_var = ft_calloc(varlen + 1, sizeof(char));
	if (!str_var)
		return (display_error_exec("bash: ", "getenv_var: ", 6), NULL);
	i = -1;
	while (name[++i])
		str_var[i] = name[i];
	str_var[i] = '=';
	i += 1;
	j = -1;
	while (value[++j])
		str_var[i + j] = value[j];
	return (str_var);
}

char	*getexport_var(char *name, char *value)
{
	char 	*str_var;
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
	return (str_var);
}

char	**ft_getenv(t_msl *ms, int mode)
{
	t_var	*tmp_env;
	char 	**getenv;
	int		nb_var;
	int		i;

	nb_var = envsize(ms);
	getenv = ft_calloc(nb_var + 1, sizeof(char *));
	if (!getenv)
		return (display_error_exec("bash: ", "ms->env: ", 6), NULL);
	if (nb_var == 0)
		return (display_error_exec("bash: ", "getenv: ", 8), NULL);
	tmp_env = ms->env;
	i = 0;
	while (tmp_env != NULL)
	{
		if (mode == 0)
			getenv[i] = getenv_var(tmp_env->name, tmp_env->value);
		else if (mode == 1)
			getenv[i] = getexport_var(tmp_env->name, tmp_env->value);
		tmp_env = tmp_env->next;
		i++;
	}
	return (getenv);
}

// int	in_export(t_msl *ms, t_var *var)
// {
// 	t_var	*tmp_env;

// 	if (!ms->export->name)
// 		return (0);
// 	tmp_env = ms->export;
// 	while (tmp_env != NULL)
// 	{
// 		printf("Test\n");
// 		if (strict_cmp(tmp_env->name, var->name))
// 			return (1);
// 		tmp_env = tmp_env->next;
// 	}
// 	return (0);
// }

int	in_export(t_msl *ms, char *var)
{
	t_var	*tmp_env;

	if (!ms->export->name)
		return (0);
	tmp_env = ms->export;
	while (tmp_env != NULL)
	{
		printf("Test\n");
		if (strict_cmp(tmp_env->name, var))
			return (1);
		tmp_env = tmp_env->next;
	}
	return (0);
}

int	len_biggest(char *s1, char *s2)
{
	int	len_s1;
	int	len_s2;

	len_s1 = ft_strlen_null(s1);
	len_s2 = ft_strlen_null(s2);
	if (len_s1 > len_s2)
		return (len_s1);
	if (len_s1 < len_s2)
		return (len_s2);
	return (len_s1);
}

int	len_until_eq(char *s1, char *s2)
{
	int	len_s1;
	int	len_s2;

	// len_s1 = ft_strlen_null(s1);
	// len_s2 = ft_strlen_null(s2);
	len_s1 = 0;
	len_s2 = 0;
	while (s1[len_s1] && s1[len_s1] != '=')
		len_s1++;
	while (s2[len_s2] && s2[len_s2] != '=')
		len_s2++;
	// printf("%d %d\n", len_s1, len_s2);
	if (len_s1 > len_s2)
		return (len_s1);
	if (len_s1 < len_s2)
		return (len_s2);
	return (len_s1);
}

void	add_sorted(t_msl *ms, t_var *var)
{
	t_var	*add_back;

	if (!var)
		return ;
	if (!ms->export->name)
	{
		// printf("first\n");
		ms->export = var;
		// env = var;
	}
	else
	{
		add_back = ms->export;
		while (add_back->next != NULL)
		{
			// printf("%s\n", add_back->name);
			add_back = add_back->next;
		}
		add_back->next = var;
	}
	// printf("%s\n", (*env)->name);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t			i;
	int				return_value;
	int			len_biggest;
	int		c;
	// unsigned char	*str_1;
	// unsigned char	*str_2;

	i = 0;
	return_value = 0;
	len_biggest = len_until_eq(s1, s2);
	// str_1 = (unsigned char *)s1;
	// str_2 = (unsigned char *)s2;
	while (i < len_biggest)
	{
		if ((s1[i] == '=' || !s1[i]) && s2[i])
		{
			c = -(int)s2[i];
			// printf("end s1 value : %d\n", c);
			return (c);
		}
		else if ((s2[i] == '=' || !s2[i]) && s1[i])
		{
			c = (int)s1[i];
			// printf("end s2 value : %d\n", c);
			return (c);
		}
		else if (s1[i] != s2[i])
		{
			return_value = s1[i] - s2[i];
			// printf("%c %c", s1[i], s2[i]);
			return (return_value);
		}
		i++;
	}
	return (0);
}

void	*getenv_sorted(t_msl *ms)
{
	int		i;
	int		j;
	int		index;
	int		order;
	char	**arr_export;

	i = -1;
	arr_export = ft_getenv(ms, 1);
	order = 0;
	while (arr_export[++i])
	{
		index = 0;
		j = -1;
		while (arr_export[++j])
		{
			if (ft_strcmp(arr_export[i], arr_export[j]) > 0)
				index++;
		}
		if (index == order)
		{
			printf("declare -x %s\n", arr_export[i]);
			order++;
			i = -1;
		}
	}
	ft_arrfree(arr_export);
}

// mode 0 == display env, mode 1 == display_export
void	display_env(t_msl *ms, int mode)
{
	t_var	*vars;

	if (ms->env->name)
	{
		vars = ms->env;
		while (vars != NULL)
		{
			if (vars->in_env && mode == 0)
				printf("%s=%s\n", vars->name, vars->value);
			else if (mode == 1)
				getenv_sorted(ms);
			vars = vars->next;
		}
	}
	if (mode == 0)
		printf("_=/usr/bin/env\n");
}

void	var_add_back(t_msl *ms, t_var *var)
{
	t_var	*add_back;

	if (!ms->env->name)
		ms->env = var;
	else
	{
		add_back = ms->env;
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

char	**split_equal(char *env_var)
{
	char	**split_equal;
	int		i;
	int		len;
	int		len_two;

	// if (!ft_strchr(env_var, '='))
	// 	return (ft_split(env_var, '='));
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

	i = -1;
	ms->env = ft_calloc(ft_arrlen(envp) + 1, sizeof(t_var *));
	if (!envp[0])
	{
		// display_error_exec("bash: ", "ms->env: ", 6);
		printf("add only variables needed\n");
		return ;
	}
	// printf("Test %d\n", ft_arrlen(envp));
	while (envp[++i])
	// while (i++ < 0)
	{
		// printf("%s\n", envp[i]);
		tmp_split = split_equal(envp[i]);
		if (!strict_cmp(tmp_split[0], "_"))
			var_add_back(ms, new_var(tmp_split[0], tmp_split[1], 1));
	}
}
