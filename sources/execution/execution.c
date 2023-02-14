/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:49:25 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/02/14 22:01:24 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

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
	free(cmd_path);
	ft_arrfree(cmd_args);
	// exit(0);
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

void	builtins_execution(t_msl *ms, char **envp, char **args_cmd)
{
	(void)ms;
	(void)envp;

	char	*tmp_path;
	char	**tmp_args;

	tmp_path = get_cmd_path(args_cmd[0], envp);
	tmp_args = ft_calloc(1, sizeof(char *));
	tmp_args = ft_arradd_back(tmp_args, tmp_path);

	// ft_printf("%s\n", tmp_args[0]);

	// ft_printf("Builtins function : %s\n", tmp_path[0]);
	if (strict_cmp("echo", args_cmd[0]))
		ft_printf("echo execution\n");
	else if (strict_cmp("cd", args_cmd[0]))
	{
		if (ft_arrlen(args_cmd) > 2)
			ft_printf("bash: cd: too many arguments\n");
		else if (ft_arrlen(args_cmd) == 2)
		{
			// test if valid folder
			if (access(args_cmd[1], X_OK) == 0)
			{
				// if no other cmd change directory
				if (ms->c_pipe == 0)
					chdir(args_cmd[1]);
			}
			else
				ft_printf("bash: cd: %s: No such file or directory\n", args_cmd[1]);
		}
		else
		{
			// if only cd check if no pipe to change directory
			if (ms->c_pipe == 0)
				chdir(getenv("HOME"));
				// change to root dir
		}
	}
	else if (strict_cmp("pwd", args_cmd[0]))
	{
		tmp_args = ft_arradd_back(tmp_args, tmp_path);
		execve(tmp_path, tmp_args, NULL);
	}
	else if (strict_cmp("export", args_cmd[0]))
		ft_printf("export execution\n");
	else if (strict_cmp("unset", args_cmd[0]))
		ft_printf("unset execution\n");
	else if (strict_cmp("env", args_cmd[0]))
		ft_printf("env execution\n");
	else if (strict_cmp("exit", args_cmd[0]))
	{
		if (ms->c_pipe == 0)
			exit (0);
	}
}

void	standard_execution(t_msl *ms, char **envp, char **args_cmd)
{
	(void)ms;
	(void)envp;
	ft_printf("Classic function : %s\n", args_cmd[0]);
	create_pipe(args_cmd, ms, envp);
}

void	execution(t_msl *ms, char *input, char **envp)
{
	char	*input_test = "/usr/bin/ls \"-l\" '-a'";
	char	*args_cmd[] = {"/usr/bin/ls", "'-'l", "-a", NULL};
	char	*input_echo = "echo \"phrase\" 'a la con'";
	char	*arr_echo[] = {"/usr/bin/echo", "'~' une phra\"se \"exemple avec \
'un vrai $PWD' qui ne s\"'\"affichera qu\"'\"entre double quote \"$PWD\"", "'", NULL};

	char	***cmds;
	char	**tmp_split;
	int	i;

	ms->c_pipe = count_pipes(input);
	ms->cmds = ft_calloc(ms->c_pipe + 1, sizeof(char **));
	ms->split = ft_split(input, '|');
	i = -1;
	while (ms->split[++i])
		ms->cmds[i] = ft_split(ms->split[i], ' ');
	for (int i = 0; i <= ms->c_pipe; i++)
	{
		if (is_builtins(ms->cmds[i][0]))
			builtins_execution(ms, envp, ms->cmds[i]);
		else
			standard_execution(ms, envp, ms->cmds[i]);
	}
}
