/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:13:51 by msapin            #+#    #+#             */
/*   Updated: 2023/04/04 16:19:38 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_homepath(t_msl *ms)
{
	t_var	*tmp_var;

	tmp_var = getvar(ms, "HOME");
	ms->status = 1;
	if (!tmp_var)
		return (display_error_exec("minishell: cd: ", NULL, 16), NULL);
	return (tmp_var->value);
}

char	*get_trim_path(t_msl *ms, char *path)
{
	char	*path_home;
	char	*trim_path;
	int		len_path;
	int		i;

	path_home = get_homepath(ms);
	if (!path_home)
		return (NULL);
	len_path = ft_strlen_null(path_home) + ft_strlen_null(path);
	trim_path = ft_calloc(len_path + 1, sizeof(char));
	if (!trim_path)
		return (free(path_home), NULL);
	i = -1;
	while (path_home[++i])
		trim_path[i] = path_home[i];
	trim_path[i] = '/';
	ft_strlcat(trim_path, path + 1, len_path + 2);
	return (trim_path);
}

static int	rtn_error_cd(char c)
{
	display_error_exec("minishell: cd: -", &c, 1);
	return (2);
}

static int	is_cd_valid(t_msl *ms, char **args_cmd, int mode)
{
	char	*trim_path;

	if (mode == 1)
	{
		if (ft_strlen(args_cmd[1]) > 2)
			return (rtn_error_cd(args_cmd[1][1]));
		else if (ft_strlen(args_cmd[1]) == 2)
			if (args_cmd[1][1] != '-')
				return (rtn_error_cd(args_cmd[1][1]));
	}
	else if (mode == 2)
	{
		trim_path = get_trim_path(ms, args_cmd[1]);
		if (!trim_path)
			return (1);
		if (trim_path && access(trim_path, X_OK) != 0)
			return (free(trim_path), display_error_exec("minishell: cd: ",
					args_cmd[1], 2), 1);
		free(trim_path);
	}
	return (0);
}

int	check_arg_cd(t_msl *ms, char **args_cmd)
{
	int	valid;

	valid = 0;
	if (args_cmd[1][0] == '-')
		valid = is_cd_valid(ms, args_cmd, 1);
	else if (args_cmd[1][0] == '~')
		valid = is_cd_valid(ms, args_cmd, 2);
	else if (access(args_cmd[1], X_OK) != 0)
	{
		if (access(args_cmd[1], F_OK) == 0)
			display_error_exec("minishell: cd: ", args_cmd[1], 12);
		else
			display_error_exec("minishell: cd: ", args_cmd[1], 2);
		valid = 1;
	}
	return (valid);
}
