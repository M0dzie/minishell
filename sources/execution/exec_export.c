/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:43:24 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/03/21 13:53:07 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minimehdi.h"

int	invalid_first(char *name)
{
	char	*invalid_char;
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
	char	*invalid_opt;
	int		i;
	int		namelen;

	namelen = ft_strlen(name);
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
	char	*invalid_char;
	int		i;
	int		j;

	if (invalid_first(name))
		return (display_error_exec("bash: export: '", name, 14), 1);
	else if (invalid_option(name))
		return (2);
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

void	var_handling(t_msl *ms, char *args_cmd)
{
	t_var	*tmp_var;
	char	**tmp_split;

	if (ft_strchr(args_cmd, '='))
	{
		tmp_split = split_equal(args_cmd);
		tmp_var = getvar(ms, tmp_split[0]);
		if (tmp_var)
		{
			tmp_var->value = tmp_split[1];
			tmp_var->in_env = 1;
		}
		else
			var_add_back(ms, new_var(tmp_split[0], tmp_split[1], 1));
		ft_arrfree(ms->arrenv);
		ms->arrenv = ft_getenv(ms, 0);
	}
	else
	{
		tmp_var = getvar(ms, args_cmd);
		if (!tmp_var)
			var_add_back(ms, new_var(args_cmd, NULL, 0));
	}
}

int	exec_export(t_msl *ms, char **args_cmd)
{
	int		i;
	int		exit_stat;

	i = 0;
	exit_stat = 0;
	if (ft_arrlen(args_cmd) == 1)
		display_env(ms, 1);
	while (args_cmd[++i])
	{
		exit_stat = invalid_identifier(args_cmd[i]);
		if (exit_stat == 0 && ms->c_pipe == 0)
			var_handling(ms, args_cmd[i]);
	}
	return (exit_stat);
}
