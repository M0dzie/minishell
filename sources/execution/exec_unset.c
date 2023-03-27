/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:44:39 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/03/27 11:12:49 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	invalid_option_unset(char *name)
{
	char	*invalid_opt;
	int		i;
	int		namelen;

	namelen = ft_strlen(name);
	if (name[0] == '-' && namelen > 1)
	{
		invalid_opt = ft_calloc(3, sizeof(char));
		if (!invalid_opt)
			return (display_error_exec("minishell: ", "invalid_opt: ", 6), 1);
		invalid_opt[0] = name[0];
		invalid_opt[1] = name[1];
		return (display_error_exec("minishell: unset: ", invalid_opt, 1), 1);
	}
	return (0);
}

int	invalid_identifier_unset(char *name)
{
	char	*invalid_char;
	int		i;
	int		j;

	if (!name[0])
		return (display_error_exec("minishell: unset: '", name, 14), 1);
	if (invalid_option_unset(name))
		return (2);
	invalid_char = "`&*/\\{}[]";
	i = -1;
	while (name[++i])
	{
		j = -1;
		while (invalid_char[++j])
		{
			if (name[i] == invalid_char[j])
				return (display_error_exec("minishell: unset: '", name, 14), 1);
		}
	}
	return (0);
}

t_var	*get_previous_var(t_msl *ms, char *var_name)
{
	t_var	*prev;

	prev = ms->env;
	while (prev->next != NULL)
	{
		if (ft_strmatch(prev->next->name, var_name))
			return (prev);
		prev = prev->next;
	}
	prev = NULL;
	return (prev);
}

void	unset_handling(t_msl *ms, char *var_name)
{
	t_var	*tmp_var;
	t_var	*tmp_prev;
	t_var	*tmp_next;

	tmp_var = getvar(ms, var_name);
	if (tmp_var)
	{
		tmp_prev = get_previous_var(ms, var_name);
		tmp_next = tmp_var->next;
		if (tmp_next == NULL && tmp_prev)
		{
			// printf("unset last var\n");
			free(tmp_var);
			tmp_prev->next = NULL;
		}
		else if (tmp_prev == NULL && tmp_next)
		{
			// printf("unset first var\n");
			ms->env = tmp_next;
			free(tmp_prev);
		}
		else if (tmp_next == NULL && tmp_prev == NULL)
		{
			tmp_var->name = NULL;
			tmp_var->value = NULL;
			// free(ms->env);
			// printf("%s is the only var in env\n", tmp_var->name);
		}
		else
		{
			// printf("var in middle\n");
			free(tmp_var);
			tmp_prev->next = tmp_next;
		}
		// ft_arrfree(ms->arrenv);
		// ft_arrfree(ms->arrexport);
		ms->arrenv = ft_getenv(ms);
		ms->arrexport = ft_getexport(ms);
	}
}

int	exec_unset(t_msl *ms, char **args_cmd)
{
	int		i;
	int		valid;
	int		rtn;

	i = 0;
	rtn = 0;
	while (args_cmd[++i])
	{
		valid = invalid_identifier_unset(args_cmd[i]);
		if (valid == 0 && ms->c_pipe == 0)
			unset_handling(ms, args_cmd[i]);
		else
			rtn = valid;
	}
	return (rtn);
}
