/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:43:24 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/02/23 16:38:56 by msapin           ###   ########.fr       */
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

int	add_env_var(t_msl *ms)
{

	return (0);
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

int	invalid_first(char c)
{
	char 	*invalid_char;
	int		i;

	invalid_char = "1234567890=";
	i = -1;
	while (invalid_char[++i])
	{
		if (invalid_char[i] == c)
			return (1);
	}
	return (0);
}

int	invalid_identifier(char *name)
{
	char 	*invalid_char;
	int		i;
	int		j;

	if (invalid_first(name[0]))
		return (display_error_exec("bash: export: '", name, 14), 1);
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

int	exec_export(t_msl *ms, char **args_cmd, char **envp)
{
	// printf("execution of export\n");
	t_var	*tmp_var;
	t_var	*tmp_last;
	char	**tmp_split;
	int		i;
	int		valid;

	// if (ms->c_pipe == 0 && args_cmd[1] && ft_strchr(args_cmd[1], '='))
	// {
	// 	tmp_split = split_equal(args_cmd);
	// 	tmp_var = getvar(ms, args_cmd[1]);
	// 	// if (is_in_env(ms, args_cmd[1]))
	// 	if (tmp_var)
	// 	{
	// 		printf("%s is already in env\n", args_cmd[1]);
	// 		tmp_var->value = "Test";
	// 	}
	// 	else
	// 	{
	// 		tmp_last = getlast_var(ms);
	// 		tmp_last->value = "test_add";
	// 		printf("%s add after %s\n", args_cmd[1], tmp_last->name);
	// 	}
	// }
	i = 0;
	valid = 0;
	while (args_cmd[++i])
	{
		// printf("%d/ %s\n", i, args_cmd[i]);
		if (invalid_identifier(args_cmd[i]))
		{
			// printf("invalid identifier\n");
			valid = 1;
		}
		if (valid == 0 && ms->c_pipe == 0)
			printf("ADD %s\n", args_cmd[i]);
	}
	return (valid);
}
