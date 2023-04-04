/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:38:38 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/04/04 14:07:56 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_env(char *arg)
{
	if (ft_strlen(arg) != 3)
		return (0);
	if (!(arg[0] == 'e' && arg[1] == 'n' && arg[2] == 'v'))
		return (0);
	return (1);
}

int	is_denied(char *arg)
{
	if (access(arg, W_OK) == 0)
		return (display_error_exec("env: '", arg, 13), -1);
	return (0);
}

int	cmd_valid(t_msl *ms, char **arg)
{
	char	*paths;
	char	**tmp_paths;
	char	*join_one;
	char	*join_two;
	int		i;

	i = -1;
	paths = getvar(ms, "PATH")->value;
	tmp_paths = ft_split(paths, ':');
	while (tmp_paths[++i])
	{
		join_one = ft_strjoin(tmp_paths[i], "/");
		join_two = ft_strjoin(join_one, arg[0]);
		if (access(join_two, F_OK) == 0)
			return (free(join_one), free(join_two), ft_arrfree(tmp_paths), 1);
		free(join_one);
		free(join_two);
	}
	return (ft_arrfree(tmp_paths), 0);
}

int	exec_env(t_msl *ms, char **args_cmd)
{	
	int	nb_args;
	int	i;

	if (!getvar(ms, "PATH") && !match_multi("/usr/bin/env", "/bin/env", NULL, 
	args_cmd[0]))
		return (display_error_exec("env: ", args_cmd[0], 2), 127);
	nb_args = ft_arrlen(args_cmd);
	if (nb_args > 1)
	{
		i = 0;
		while (args_cmd[++i])
		{
			if (!is_env(args_cmd[i]))
			{
				if (cmd_valid(ms, args_cmd + i) && args_cmd[i][0] != '.')
					return (execute_cmd(ms, ft_arrdup(args_cmd + i)), 0);
				else if (access(args_cmd[i], F_OK))
					return (display_error_exec("env: ", args_cmd[i], 2), 127);
				else if (is_denied(args_cmd[i]))
					return (126);
			}
		}
	}
	display_env(ms, ENV);
	return (0);
}
