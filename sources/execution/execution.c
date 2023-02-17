/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:49:25 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/02/17 23:40:08 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

int	display_error_exec(char *first, char *second, int num_error)
{	
	char	*err[15];		// to correct

	// err[1] = ": wrong function call\n\nexpected: ./pipex file1 cmd1 ... \
cmd* file2    or    ./pipex here_doc LIMITER cmd cmd1 file";
	err[2] = ": no such file or directory: ";
	err[3] = ": environnement PATH not found";
	err[4] = ": environnement SHELL not found";
	err[5] = ": command not found";
	err[6] = "cannot allocate memory : ";
	err[7] = ": cannot create or modify: ";
	err[8] = ": environnement VARIABLES not found";
	err[9] = ": warning: here-document delimited by end-of-file, wanted: ";
	err[10] = "too many arguments";
	err[11] = ": numeric argument required";
	ft_putstr_fd(first, 2);
	ft_putstr_fd(second, 2);
	ft_putendl_fd(err[num_error], 2);
	return (-1);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	char	**tmp_paths;
	char	*join_one;
	char	*join_two;
	int		i;

	i = -1;
	tmp_paths = ft_split(getenv("PATH"), ':');
	while (tmp_paths[++i])
	{
		join_one = ft_strjoin(tmp_paths[i], "/");
		join_two = ft_strjoin(join_one, cmd);
		if (access(join_two, F_OK) == 0)
			return (ft_arrfree(tmp_paths), free(join_one), join_two);
		free(join_one);
		free(join_two);
	}
	return (ft_arrfree(tmp_paths), ft_strdup(cmd));
}

void	execute_cmd(char **cmd_args, char **envp)
{
	char	*cmd_path;

	if (ft_strchr(cmd_args[0], '/'))
		cmd_path = ft_strdup(cmd_args[0]);
	else
		cmd_path = get_cmd_path(cmd_args[0], envp);
	execve(cmd_path, cmd_args, envp);
	display_error_exec("bash: ", cmd_args[0], 5);
	free(cmd_path);
	ft_arrfree(cmd_args);
	exit(127);
}

void	create_pipe(char **args_cmd, t_msl *ms, char **envp)
{
	(void)args_cmd;
	(void)ms;

	pid_t	pid;

	pid = fork();
	if (pid == 0)
		execute_cmd(args_cmd, envp);
	else
		wait(NULL);
}

int	strict_cmp(const char *builts, const char *cmd)
{
	size_t	i;
	size_t	cmd_len;

	i = -1;
	cmd_len = ft_strlen(cmd);
	if (ft_strlen(builts) != ft_strlen(cmd))
		return (0);
	while (++i < cmd_len)
	{
		if (builts[i] != cmd[i])
			return (0);
	}
	return (1);
}

int	is_builtins(char *cmd)
{
	char	*tmp_cmd;
	char	**tmp_split;

	if (ft_strchr(cmd, '/'))
	{
		tmp_split = ft_split(cmd, '/');
		tmp_cmd = tmp_split[ft_arrlen(tmp_split) - 1];
	}
	else
		tmp_cmd = ft_strdup(cmd);
	if (strict_cmp("echo", tmp_cmd) | strict_cmp("cd", tmp_cmd) | 
		strict_cmp("pwd", tmp_cmd) | strict_cmp("export", tmp_cmd) |
		strict_cmp("unset", tmp_cmd) | strict_cmp("env", tmp_cmd) |
		strict_cmp("exit", tmp_cmd))
		return (1);
	return (0);
}

void	exec_pwd(t_msl *ms, char **args_cmd, char **envp)
{
	char	*tmp_path;
	char	**tmp_args;
	int		i;
	int		valid;

	tmp_path = get_cmd_path(args_cmd[0], envp);
	tmp_args = ft_calloc(1, sizeof(char *));
	tmp_args = ft_arradd_back(tmp_args, tmp_path);
	valid = 1;
	if (args_cmd[1])
	{
		if (args_cmd[1][0] == '-')
		{
			if (ft_strlen(args_cmd[1]) > 2)
			{
				valid = 0;
				ft_printf("bash: pwd: -%c: invalid option\n", args_cmd[1][1]);		// call display error
			}
			else if (ft_strlen(args_cmd[1]) == 2)
			{
				if (args_cmd[1][1] != '-')
				{
					valid = 0;
					ft_printf("bash: pwd: -%c: invalid option\n", args_cmd[1][1]);		// call display error
				}
			}
		}
	}
	if (valid)
		create_pipe(tmp_args, ms, envp);
}

void	change_dir(t_msl *ms, char *path)
{
	if (ms->c_pipe == 0)
		chdir(path);
}

void	exec_cd(t_msl *ms, char **args_cmd)
{
	if (ft_arrlen(args_cmd) > 2)
		ft_printf("bash: cd: too many arguments\n");
	else if (ft_arrlen(args_cmd) == 2)
	{
		// test if valid folder
		if (access(args_cmd[1], X_OK) == 0)
			change_dir(ms, args_cmd[1]);
		else if (access(args_cmd[1], F_OK) == 0)
			ft_printf("bash: cd: %s: Not a directory\n", args_cmd[1]);
		else
			ft_printf("bash: cd: %s: No such file or directory\n", args_cmd[1]);
	}
	else
		change_dir(ms, getenv("HOME"));
}

int	is_onlynum(char *arg)
{
	int	i;
	int	lenstr;

	i = -1;
	lenstr = ft_strlen(arg);
	if (lenstr == 1 && (arg[0] == '-' || arg[0] == '+'))
		return (0);
	else if (lenstr > 1)
	{
		if (arg[0] == '-' || arg[0] == '+')
			i++;
	}
	while (arg[++i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
	}
	return (1);
}

void	display_exit(int exit_nb, int num_error, char *arg)
{
	if (num_error > 0)
	{
		ft_putendl_fd("exit", 2);
		display_error_exec("bash: exit: ", arg, num_error);
	}
	else
		ft_putendl_fd("exit", 1);
	exit (exit_nb);
}

void	exec_exit(t_msl *ms, char **args_cmd)
{
	if (ms->c_pipe == 0)
	{	
		if (ft_arrlen(args_cmd) > 2)
		{
			if (is_onlynum(args_cmd[1]))
			{
				display_exit(1, 10, NULL);
				// ft_printf("bash: exit: too many arguments\n");
			}
			else
				display_exit(2, 11, args_cmd[1]);
				// ft_printf("bash: exit: FIRST_ARG: numeric argument required\n");
		}
		else if (ft_arrlen(args_cmd) == 2)
		{
			if (is_onlynum(args_cmd[1]))
				display_exit(ft_atoi(args_cmd[1]), 0, NULL);
				// ft_printf("Exit valid with number to user with : %s\n", args_cmd[1]);
			else
				display_exit(2, 11, args_cmd[1]);
				// ft_printf("bash: exit: FIRST_ARG: numeric argument required\n");
		}
		else
			display_exit(0, 0, NULL);
	}
}

void	builtins_execution(t_msl *ms, char **args_cmd, char **envp)
{
	(void)ms;
	(void)envp;

	// char	*tmp_path;
	// char	**tmp_args;

	// tmp_path = get_cmd_path(args_cmd[0], envp);
	// tmp_args = ft_calloc(1, sizeof(char *));
	// tmp_args = ft_arradd_back(tmp_args, tmp_path);

	// ft_printf("%s\n", tmp_args[0]);

	// ft_printf("Builtins function : %s\n", tmp_path[0]);
	if (strict_cmp("echo", args_cmd[0]))
		ft_printf("echo execution\n");
	else if (strict_cmp("cd", args_cmd[0]))		// WIP
		exec_cd(ms, args_cmd);
	else if (strict_cmp("pwd", args_cmd[0]))		// DONE
		exec_pwd(ms, args_cmd, envp);
	else if (strict_cmp("export", args_cmd[0]))
		ft_printf("export execution\n");
	else if (strict_cmp("unset", args_cmd[0]))
		ft_printf("unset execution\n");
	else if (strict_cmp("env", args_cmd[0]))
		ft_printf("env execution\n");
	else if (strict_cmp("exit", args_cmd[0]))
	{
		// if (ms->c_pipe == 0)
		// 	exit (0);
		exec_exit(ms, args_cmd);
	}
}

void	standard_execution(t_msl *ms, char **args_cmd, char **envp)
{
	(void)ms;
	(void)envp;
	// ft_printf("Classic function : %s\n", args_cmd[0]);
	create_pipe(args_cmd, ms, envp);
}

void	execution(t_msl *ms, char *input, char **envp)
{
	char	*arr_echo[] = {"/usr/bin/echo", "'~' une phra\"se \"exemple avec \
'un vrai $PWD' qui ne s\"'\"affichera qu\"'\"entre double quote \"$PWD\"", "'", NULL};

	for (int i = 0; i <= ms->c_pipe; i++)
	{
		if (is_builtins(ms->cmds[i][0]))
			builtins_execution(ms, ms->cmds[i], envp);
		else
			standard_execution(ms, ms->cmds[i], envp);
	}
}
