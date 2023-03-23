/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 09:46:41 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/03/23 19:51:31 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_homepath(t_msl *ms)
{
	t_var	*tmp_var;

	tmp_var = getvar(ms, "HOME");
	ms->status = 1;
	if (!tmp_var)
		return (display_error_exec("bash: cd: ", NULL, 16), NULL);
	return (tmp_var->value);
}

int	change_dir(t_msl *ms, char *path, char **envp)
{
	t_var	*tmp_var;
	char	buf_pwd[BUFSIZ];
	char	buf_oldpwd[BUFSIZ];
	int		valid_dir;
	char	*tmp_old;

	// printf("%s\n", path);
	if (ms->c_pipe == 0)
	{
		tmp_old = getcwd(buf_oldpwd, BUFSIZ);
		valid_dir = chdir(path);
		if (valid_dir == 0)
		{
			tmp_var = getvar(ms, "OLDPWD");
			if (tmp_var)
				tmp_var->value = tmp_old;
			tmp_var = getvar(ms, "PWD");
			if (tmp_var)
				tmp_var->value = getcwd(buf_pwd, BUFSIZ);
			ms->pwd = getcwd(buf_pwd, BUFSIZ);
			// printf("pwd : %s\noldpwd : %s\n", getvar(ms, "PWD")->value, getvar(ms, "OLDPWD")->value);
			ms->arrenv = ft_getenv(ms);
			ms->arrexport = ft_getexport(ms);
		}
		
	}
	if (!path)
		return (1);
	return (0);
}

int	rtn_error_cd(char c)
{
	display_error_exec("bash: cd: -", &c, 1);
	return (2);
}

char	*get_trim_path(t_msl *ms, char *path)
{
	char	*path_home;
	char	*trim_path;
	int		len_path;
	int		i;

	// path_home = getenv("HOME");
	path_home = get_homepath(ms);
	// printf("%s\n", path_home);
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

int	is_cd_valid(t_msl *ms, char **args_cmd, int mode)
{
	char	*trim_path;

	// printf("is_cd_valid\n");

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
		trim_path = get_trim_path(ms, args_cmd[1]);
		printf("-%s-\n", trim_path);
		if (access(trim_path, X_OK) != 0)
			return (display_error_exec("bash: cd: ", args_cmd[1], 2), 1);
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
			display_error_exec("bash: cd: ", args_cmd[1], 12);
		else
			display_error_exec("bash: cd: ", args_cmd[1], 2);
		valid = 1;
	}
	return (valid);
}

int	exec_cd(t_msl *ms, char **args_cmd)
{
	int	args_len;
	int	exit_stat;

	args_len = ft_arrlen(args_cmd);
	exit_stat = 0;
	if (args_len > 2)
	{
		display_error_exec("bash: cd: ", NULL, 10);
		exit_stat = 1;
	}
	else if (args_len == 2)
	{
		exit_stat = check_arg_cd(ms, args_cmd);
		if (exit_stat == 0)
		{
			if (args_cmd[1][0] == '-')
				change_dir(ms, get_trim_path(ms, getvar(ms, "OLDPWD")->value), ms->arrenv);		// fix getenv
			else if (args_cmd[1][0] == '~')
				change_dir(ms, get_trim_path(ms, args_cmd[1]), ms->arrenv);
			else
				change_dir(ms, args_cmd[1], ms->arrenv);
		}
	}
	else
		exit_stat = change_dir(ms, get_homepath(ms), ms->arrenv);
	// printf("exit nb %d\n", exit_stat);
	// exit (exit_stat);
	return (exit_stat);
}
