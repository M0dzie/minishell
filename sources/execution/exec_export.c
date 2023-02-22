/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:43:24 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/02/22 15:38:39 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	rm_env_var(t_msl *ms)
// {
// 	t_var	tmp_stack;

// 	tmp_stack = ms->env;
// 	while
// }

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

void	exec_export(t_msl *ms, char **args_cmd, char **envp)
{
	printf("execution of export\n");

	if (ms->c_pipe == 0 && args_cmd[1])
	{
		if (is_in_env(ms, args_cmd[1]))
			printf("Is already in env\n");
	}
}
