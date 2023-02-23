/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:43:24 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/02/23 21:04:24 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minimehdi.h"

// void	rm_env_var(t_msl *ms)
// {
// 	t_var	tmp_stack;

// 	tmp_stack = ms->env;
// 	while
// }

t_var	*getlast_var(t_msl *ms)
{
	t_var	*tmp_stack;

	tmp_stack = ms->env;
	while (tmp_stack->next != NULL)
	{
		tmp_stack = tmp_stack->next;
	}
	return (tmp_stack);
}

int	is_in_env(t_msl *ms, char *var_name)
{
	t_var *tmp_stack;

	tmp_stack = ms->env;
	while (tmp_stack != NULL)
	{
		printf("%s\n", tmp_stack->name);
		tmp_stack = tmp_stack->next;
	}
	return (0);
}

int	invalid_first(char *name)
{
	char 	*invalid_char;
	int		i;

	invalid_char = "1234567890=";
	i = -1;
	while (invalid_char[++i])
	{
		if (invalid_char[i] == name[0])
			return (1);
	}
	return (0);
}

int	invalid_option(char *name)
{
	char 	*invalid_opt;
	int		i;
	int		namelen;

	namelen = ft_strlen(name) ;
	if (name[0] == '-' && namelen > 1)
	{
		invalid_opt = ft_calloc(3, sizeof(char));
		if (!invalid_opt)
			return (display_error_exec("bash: ", "getenv_var: ", 6), 1);
		invalid_opt[0] = name[0];
		invalid_opt[1] = name[1];
		return (display_error_exec("bash: export: ", invalid_opt, 1), 1);
	}
	return (0);
}

int	invalid_identifier(char *name)
{
	char 	*invalid_char;
	int		i;
	int		j;

	if (invalid_first(name))
		return (display_error_exec("bash: export: '", name, 14), 1);
	else if (invalid_option(name))
		return (1);
	invalid_char = "`~!@#$%^&*-+.,/\\?:{}[]";
	i = -1;
	while (name[++i])
	{
		j = -1;
		while (invalid_char[++j])
		{
			if (name[i] == invalid_char[j])
				return (display_error_exec("bash: export: '", name, 14), 1);
		}
	}
	return (0);
}

int	add_env_var(t_msl *ms)
{

	return (0);
}

int	exec_export(t_msl *ms, char **args_cmd, char **envp)
{
	t_var	*tmp_var;
	char	**tmp_split;
	int		i;
	int		valid;

	i = 0;
	valid = 0;
	if (ft_arrlen(args_cmd) == 1)
		printf("display export\n");
	while (args_cmd[++i])
	{
		if (invalid_identifier(args_cmd[i]))
			valid = 1;
		if (valid == 0 && ms->c_pipe == 0 && ft_strchr(args_cmd[i], '='))
		{
			tmp_split = split_equal(args_cmd[i]);
			tmp_var = getvar(ms, tmp_split[0]);
			if (tmp_var)
				tmp_var->value = tmp_split[1];
			else
				var_add_back(ms, new_var(tmp_split[0], tmp_split[1]));
		}
		else if (valid == 0 && ms->c_pipe == 0)
			printf("add to export\n");
	}
	return (valid);
}
