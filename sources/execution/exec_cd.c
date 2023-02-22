/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 09:46:41 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/02/20 21:12:00 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

void	change_dir(t_msl *ms, char *path, char **envp)
{
	if (ms->c_pipe == 0)
		chdir(path);
}

int	rtn_error_cd(char c)
{
	display_error_exec("bash: cd: -", &c, 1);
	return (2);
}

char	*get_trim_path(char *path)
{
	char	*path_home;
	char	*trim_path;
	int		len_path;
	int		i;

	path_home = getenv("HOME");
	if (!path_home)
		return (display_error_exec("bash: cd: ", "HOME: ", 8), NULL);
	len_path = ft_strlen_null(path_home) + ft_strlen_null(path);
	trim_path = ft_calloc(len_path, sizeof(char));
	if (!trim_path)
		return (free(path_home), NULL);
	i = -1;
	while (path_home[++i])
		trim_path[i] = path_home[i];
	trim_path[i] = '/';
	ft_strlcat(trim_path, path + 1, len_path + 2);
	return (trim_path);
}

int	is_cd_valid(char **args_cmd, int mode)
{
	char	*trim_path;

	if (mode == 1)
	{
		if (ft_strlen(args_cmd[1]) > 2)
			return (rtn_error_cd(args_cmd[1][1]));
		else if (ft_strlen(args_cmd[1]) == 2)
		{
			if (args_cmd[1][1] != '-')
				return (rtn_error_cd(args_cmd[1][1]));
		}
	}
	else if (mode == 2)
	{
		trim_path = get_trim_path(args_cmd[1]);
		if (access(trim_path, X_OK) != 0)
			return (display_error_exec("bash: cd: ", args_cmd[1], 2), 1);
	}
	return (0);
}

int	check_arg_cd(char **args_cmd)
{
	int	valid;

	valid = 0;
	if (args_cmd[1][0] == '-')
		valid = is_cd_valid(args_cmd, 1);
	else if (args_cmd[1][0] == '~')
		valid = is_cd_valid(args_cmd, 2);
	else if (access(args_cmd[1], X_OK) != 0)
	{
		if (access(args_cmd[1], F_OK) == 0)
			display_error_exec("bash: cd: ", args_cmd[1], 12);
		else
			display_error_exec("bash: cd: ", args_cmd[1], 2);
		valid = 1;
	}
	return (valid);
}

void	exec_cd(t_msl *ms, char **args_cmd, char **envp)
{
	int	args_len;

	args_len = ft_arrlen(args_cmd);
	if (args_len > 2)
		display_error_exec("bash: cd: ", NULL, 10);
	else if (args_len == 2)
	{
		if (check_arg_cd(args_cmd) == 0)
		{
			if (args_cmd[1][0] == '-')
				change_dir(ms, get_trim_path(getenv("OLDPWD")), envp);
			else if (args_cmd[1][0] == '~')
				change_dir(ms, get_trim_path(args_cmd[1]), envp);
			else
				change_dir(ms, args_cmd[1], envp);
		}
	}
	else
		change_dir(ms, getenv("HOME"), envp);
}