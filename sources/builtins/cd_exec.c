/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:12:46 by msapin            #+#    #+#             */
/*   Updated: 2023/04/04 19:16:36 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_pwd(t_var *tmp_var, t_var *tmp_old, int mode)
{
	char	buf_pwd[BUFSIZ];

	if (tmp_var->value)
		free(tmp_var->value);
	if (mode == 0)
		if (tmp_old)
			if (tmp_old->value)
				tmp_var->value = ft_strdup_null(tmp_old->value);
	else if (mode == 1)
		tmp_var->value = ft_strdup_null(getcwd(buf_pwd, BUFSIZ));
}

int	change_dir(t_msl *ms, char *path_dir)
{
	t_var	*tmp_var;
	t_var	*tmp_old;
	char	buf_pwd[BUFSIZ];

	if (!path_dir)
		return (1);
	if (ms->c_pipe == 0)
	{
		tmp_old = getvar(ms, "PWD");
		if (chdir(path_dir) == 0)
		{
			tmp_var = getvar(ms, "OLDPWD");
			if (tmp_var)
			{
				if (tmp_var->value)
					free(tmp_var->value);
				tmp_var->value = ft_strdup_null(tmp_old->value);
			}
			// update_pwd(tmp_var, tmp_old, 0);
			tmp_var = getvar(ms, "PWD");
			if (tmp_var)
			{
				if (tmp_var->value)
					free(tmp_var->value);
				tmp_var->value = ft_strdup_null(getcwd(buf_pwd, BUFSIZ));
				// update_pwd(tmp_var, NULL, 1);
			}

			//	OLD VERSION
			tmp_var = getvar(ms, "OLDPWD");
			if (tmp_var)
			{
				// update_varenv(tmp_var, path_dir);
				if (tmp_var->value)
				{
				// 	printf("value exist\n");
					free(tmp_var->value);
				}
				tmp_var->value = ft_strdup_null(tmp_old->value);
			}
			tmp_var = getvar(ms, "PWD");
			if (tmp_var)
			{
				// update_varenv(tmp_var, getcwd(buf_pwd, BUFSIZ));
				if (tmp_var->value)
				{
					free(tmp_var->value);
				}
				tmp_var->value = ft_strdup_null(getcwd(buf_pwd, BUFSIZ));
			}


			update_arr(ms);
		}
	}
	return (0);
}

char	*getvar_oldpwd(t_msl *ms, char *name)
{
	t_var	*tmp_var;

	tmp_var = getvar(ms, name);
	if (!tmp_var)
		return (display_error_exec("minishell: cd: ", name, 17), NULL);
	if (!tmp_var->value)
		return (display_error_exec("minishell: cd: ", name, 17), NULL);
	return (tmp_var->value);
}

void	handle_dir(t_msl *ms, char **args_cmd)
{
	char	*tmp_path;

	if (args_cmd[1][0] == '-')
	{
		tmp_path = getvar_oldpwd(ms, "OLDPWD");
		if (tmp_path)
		{
			printf("%s\n", tmp_path);
			change_dir(ms, tmp_path);
			free(tmp_path);
		}
	}
	else if (args_cmd[1][0] == '~')
	{
		tmp_path = get_trim_path(ms, args_cmd[1]);
		change_dir(ms, tmp_path);
		free(tmp_path);
	}
	else
		change_dir(ms, args_cmd[1]);
}

// int	exec_cd(t_msl *ms, char **args_cmd)
// {
// 	int		args_len;
// 	int		exit_stat;
// 	char	*tmp_path;

// 	args_len = ft_arrlen(args_cmd);
// 	exit_stat = 0;
// 	if (args_len > 2)
// 	{
// 		display_error_exec("minishell: cd: ", NULL, 10);
// 		exit_stat = 1;
// 	}
// 	else if (args_len == 2)
// 	{
// 		exit_stat = check_arg_cd(ms, args_cmd);
// 		if (exit_stat == 0)
// 			handle_dir(ms, args_cmd);
// 	}
// 	else
// 		exit_stat = change_dir(ms, get_homepath(ms));
// 	return (exit_stat);
// }

int	exec_cd(t_msl *ms, char **args_cmd)
{
	int	args_len;
	int	exit_stat;
	char	*tmp_path;

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
				if (getvar_oldpwd(ms, "OLDPWD"))
				{
					printf("%s\n", getvar_oldpwd(ms, "OLDPWD"));
					change_dir(ms, getvar_oldpwd(ms, "OLDPWD"));
				}
			}
			else if (args_cmd[1][0] == '~')
			{
				tmp_path = get_trim_path(ms, args_cmd[1]);
				change_dir(ms, tmp_path);
				free(tmp_path);
			}
			else
				change_dir(ms, args_cmd[1]);
		}
	}
	else
		exit_stat = change_dir(ms, get_homepath(ms));
	return (exit_stat);
}
