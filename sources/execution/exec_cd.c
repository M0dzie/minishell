/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 09:46:41 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/02/20 13:28:34 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_dir(t_msl *ms, char *path, char **envp)
{
	char	*new_old = ft_strjoin("OLDPWD=", path);
	// char	*old_pwd[] = {"export", new_old, NULL};
	char	*old_pwd[] = {"export", "TEST1=value1", NULL};

	if (ms->c_pipe == 0)
	{
		// ft_printf("old pwd : %s\n", getenv("PWD"));
		chdir(path);
		// execute_cmd(old_pwd, envp);
		// execve(old_pwd[0], old_pwd, envp);
		// create_pipe(old_pwd, ms, envp);
	}
}

int	invalid_cd(char c)
{
	display_error_exec("bash: cd: -", &c, 1);
	return (2);
}

int	check_arg_cd(char **args_cmd)
{
	int	valid;

	valid = 0;
	if (args_cmd[1][0] == '-')
	{
		if (ft_strlen(args_cmd[1]) > 2)
			valid = invalid_cd(args_cmd[1][1]);
		else if (ft_strlen(args_cmd[1]) == 2)
		{
			if (args_cmd[1][1] != '-')
				valid = invalid_cd(args_cmd[1][1]);
		}
	}
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
				// ft_printf("cd to old pwd\n");
				change_dir(ms, getenv("OLDPWD"), envp);
			else
				change_dir(ms, args_cmd[1], envp);
			// else if ()
			// change_dir(ms, args_cmd[1]);
		}
	}
	else
		change_dir(ms, getenv("HOME"), envp);
}
