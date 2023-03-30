/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 09:46:41 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/03/30 21:34:36 by mehdisapin       ###   ########.fr       */
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

int	change_dir(t_msl *ms, char *path_dir, char **envp)
{
	t_var	*tmp_var;
	char	buf_pwd[BUFSIZ];
	char	buf_oldpwd[BUFSIZ];
	int		valid_dir;
	t_var	*tmp_old;

	if (ms->c_pipe == 0)
	{
		tmp_old = getvar(ms, "PWD");
		// tmp_old = getcwd(buf_oldpwd, BUFSIZ);
		// printf("Path %s\n", path_dir);
		valid_dir = chdir(path_dir);
		if (valid_dir == 0)
		{
			tmp_var = getvar(ms, "OLDPWD");
			if (tmp_var)
			{
				// printf("value OLDPWD before %s\n", tmp_var->value);
				tmp_var->value = ft_strdup_null(tmp_old->value);
				// printf("value OLDPWD after %s\n", tmp_var->value);
			}
			tmp_var = getvar(ms, "PWD");
			if (tmp_var)
			{
				// printf("value PWD before %s\n", tmp_var->value);
				tmp_var->value = getcwd(buf_pwd, BUFSIZ);
				// printf("value PWD after %s\n", tmp_var->value);
			}
			ms->pwd = getcwd(buf_pwd, BUFSIZ);

			// printf("new dir    %s\n", ms->pwd);
			
			// printf("pwd : %s\noldpwd : %s\n", getvar(ms, "PWD")->value, getvar(ms, "OLDPWD")->value);
			ms->arrenv = ft_getenv(ms);
			ms->arrexport = ft_getexport(ms);
		}
		
	}
	if (!path_dir)
		return (1);
	return (0);
}

int	rtn_error_cd(char c)
{
	display_error_exec("minishell: cd: -", &c, 1);
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
		return (display_error_exec("minishell: cd: ", "HOME: ", 8), NULL);
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
		// printf("-%s-\n", trim_path);
		if (access(trim_path, X_OK) != 0)
			return (display_error_exec("minishell: cd: ", args_cmd[1], 2), 1);
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

char	*getvar_oldpwd(t_msl *ms, char *name)
{
	t_var	*tmp_var;

	tmp_var = getvar(ms, name);
	if (!tmp_var->value)
		// printf("No var\n");
		return (display_error_exec("minishell: cd: ", name, 17), NULL);
	// printf("OLDPWD : %s\n", tmp_var->value);
	return (tmp_var->value);
}

int	exec_cd(t_msl *ms, char **args_cmd)
{
	int	args_len;
	int	exit_stat;
	char	*tmp_path;

	// printf("exec cd\n");

	args_len = ft_arrlen(args_cmd);
	exit_stat = 0;
	if (args_len > 2)
	{
		display_error_exec("minishell: cd: ", NULL, 10);
		exit_stat = 1;
	}
	else if (args_len == 2)
	{
		exit_stat = check_arg_cd(ms, args_cmd);
		if (exit_stat == 0)
		{
			if (args_cmd[1][0] == '-')
			{
				// change_dir(ms, get_trim_path(ms, getvar(ms, "OLDPWD")->value), ms->arrenv);		// fix getenv
				tmp_path = getvar_oldpwd(ms, "OLDPWD");
				// printf("OLD_PWD : %s\n", tmp_path);
				change_dir(ms, tmp_path, ms->arrenv);		// fix getenv
			}
			else if (args_cmd[1][0] == '~')
				change_dir(ms, get_trim_path(ms, args_cmd[1]), ms->arrenv);
			else
			{
				// tmp_path = ft_strjoin(ft_strjoin(getvar_oldpwd(ms, "PWD"), "/"), args_cmd[1]);
				// change_dir(ms, tmp_path, ms->arrenv);
				change_dir(ms, args_cmd[1], ms->arrenv);
			}
		}
	}
	else
		exit_stat = change_dir(ms, get_homepath(ms), ms->arrenv);
	// printf("exit nb %d\n", exit_stat);
	// exit (exit_stat);
	return (exit_stat);
}
