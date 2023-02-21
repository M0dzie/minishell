/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:49:25 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/02/21 14:33:02 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <errno.h>
#include <stdlib.h>

int	display_error_exec(char *first, char *second, int num_error)
{	
	char	*err[15];		// to correct

	err[1] = ": invalid option";
	err[2] = ": No such file or directory";
	err[3] = ": environnement PATH not found";
	err[4] = ": environnement SHELL not found";
	err[5] = ": command not found";
	err[6] = "cannot allocate memory : ";
	err[7] = ": cannot create or modify: ";
	err[8] = ": environnement VARIABLES not found";
	err[9] = ": warning: here-document delimited by end-of-file, wanted: ";
	err[10] = "too many arguments";
	err[11] = ": numeric argument required";
	err[12] = ": Not a directory";
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

void	pipe_one(char **args_cmd, t_msl *ms, char **envp)
{
	(void)args_cmd;
	(void)ms;

	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
		execute_cmd(args_cmd, envp);
	else
		wait(NULL);
}

void	create_pipe(char **args_cmd, t_msl *ms, char **envp)
{
	(void)args_cmd;
	(void)ms;

	pid_t	pid;
	int		pipefd[2];
	int		rtn;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		execute_cmd(args_cmd, envp);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		wait(NULL);
		// waitpid(pid, &rtn, 0);
	}
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

void	builtins_execution(t_msl *ms, char **args_cmd, char **envp)
{
	(void)ms;
	(void)envp;

	if (strict_cmp("echo", args_cmd[0]))
		exec_echo(ms, args_cmd, envp);
	else if (strict_cmp("pwd", args_cmd[0]))		// DONE
		exec_pwd(ms, args_cmd, envp);
	else if (strict_cmp("env", args_cmd[0]))
		exec_env(ms, args_cmd, envp);
	else if (strict_cmp("cd", args_cmd[0]))		// WIP
		exec_cd(ms, args_cmd, envp);
	else if (strict_cmp("export", args_cmd[0]))
		exec_export(ms, args_cmd, envp);
	else if (strict_cmp("unset", args_cmd[0]))
		exec_unset(ms, args_cmd, envp);
	else if (strict_cmp("exit", args_cmd[0]))		// DONE
		exec_exit(ms, args_cmd);
}

void	handle_cmd(t_msl *ms, char **args_cmd, char **envp)
{
	if (ms->c_pipe == 0)
	{
		// printf("Just one command\n\n");
		pipe_one(args_cmd, ms, envp);
	}
	else if (ms->c_cmd == 1)
	{
		// printf("\nLast command\n");
		// execute_cmd(args_cmd, envp);
		pipe_one(args_cmd, ms, envp);
	}
	else
	{
		// printf("Command intermediaire\n");
		create_pipe(args_cmd, ms, envp);
	}
}

void	standard_execution(t_msl *ms, char **args_cmd, char **envp)
{
	handle_cmd(ms, args_cmd, envp);
}

void	execution(t_msl *ms, char *input, char **envp)
{
	char	*arr_echo[] = {"/usr/bin/echo", "'~' une phra\"se \"exemple avec \
'un vrai $PWD' qui ne s\"'\"affichera qu\"'\"entre double quote \"$PWD\"", "'", NULL};

	// ms->rtn_int = 0;
	// if (ms->c_pipe == 0)
	// 	pipe_one()
	// printf("number of cmd : %d\n", ms->c_cmd);
	for (int i = 0; i <= ms->c_pipe; i++)
	{
		if (is_builtins(ms->cmds[i][0]))
			builtins_execution(ms, ms->cmds[i], envp);
		else
			standard_execution(ms, ms->cmds[i], envp);
		ms->c_cmd--;
	}
}
