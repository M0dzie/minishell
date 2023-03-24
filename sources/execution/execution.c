/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:49:25 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/03/24 18:45:32 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <errno.h>
#include <stdlib.h>

int	display_error_exec(char *first, char *second, int num_error)
{	
	char	*err[17];		// to correct

	err[1] = ": invalid option";
	err[2] = ": No such file or directory";
	err[3] = ": environnement PATH not found";
	err[4] = ": environnement SHELL not found";
	err[5] = ": command not found";
	err[6] = "cannot allocate memory";
	err[7] = ": cannot create or modify: ";
	err[8] = ": environnement VARIABLES not found";
	err[9] = ": warning: here-document delimited by end-of-file, wanted: ";
	err[10] = "too many arguments";
	err[11] = ": numeric argument required";
	err[12] = ": Not a directory";
	err[13] = "': Permission denied";
	err[14] = "': not a valid identifier";
	err[15] = ": Cannot allocate memory";
	err[16] = ": HOME not set";
	ft_putstr_fd(first, 2);
	ft_putstr_fd(second, 2);
	ft_putendl_fd(err[num_error], 2);
	return (-1);
}

char	*get_cmd_path(t_msl *ms, char *cmd)
{
	char	**tmp_paths;
	char	*join_one;
	char	*join_two;
	int		i;
	t_var 	*tmp;

	i = -1;
	tmp = getvar(ms,"PATH");
	if (!tmp)
		return (ft_strdup(cmd));
	tmp_paths = ft_split(tmp->value, ':');
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

void	execute_cmd(t_msl *ms, char **cmd_args)
{
	char	*cmd_path;

	// ft_putendl_fd(cmd_args[0], 2);
	if (ft_strchr(cmd_args[0], '/'))
		cmd_path = ft_strdup(cmd_args[0]);
	else
		cmd_path = get_cmd_path(ms, cmd_args[0]);
	execve(cmd_path, cmd_args, ms->arrenv);
	display_error_exec("bash: ", cmd_args[0], 5);
	free(cmd_path);
	ms->status = 127;
	// free(cmd_path);
	ft_arrfree(cmd_args);
	exit (127);
}

void	exec_one(t_msl *ms, t_elem *arg)
{
	char	**args_cmd;

	args_cmd = getarr_cmd(arg);
	if (is_builtins(arg->name))
		builtins_execution(ms, arg, 0);
	ms->pid[0] = fork();
	if (ms->pid[0] < 0)
		display_error_exec("bash: ", "fork", 15);
	if (ms->pid[0] == 0)
	{
		ms->status = is_valid_builtins(ms, arg, args_cmd);
		if (match_multi("/usr/bin/env", "/bin/env", "env", args_cmd[0]) && !ms->status)
		// {
		// 	printf("exec_one\n");
			ms->status = exec_env(ms, args_cmd);
		// }
		else if (!is_builtins(arg->name))
			standard_execution(ms, arg);
		exit(ms->status);
	}
}

int	is_builtins(char *cmd)
{
	char	*tmp_cmd;
	char	**tmp_split;

	if (!cmd || !cmd[0])
		return (0);
	if (ft_strchr(cmd, '/'))
	{
		tmp_split = ft_split(cmd, '/');
		tmp_cmd = tmp_split[ft_arrlen(tmp_split) - 1];
	}
	else
		tmp_cmd = ft_strdup(cmd);
	if (ft_strmatch("echo", tmp_cmd) | ft_strmatch("pwd", tmp_cmd) |
		ft_strmatch("env", tmp_cmd) | ft_strmatch("cd", tmp_cmd) | 
		ft_strmatch("unset", tmp_cmd) | ft_strmatch("export", tmp_cmd) | 
		ft_strmatch("exit", tmp_cmd))
		return (1);
	return (0);
}

int	nb_cmd(t_elem *arg)
{
	int		nb;
	t_elem	*tmp_arg;

	nb = 0;
	tmp_arg = arg;
	while (tmp_arg != NULL)
	{
		nb++;
		tmp_arg = tmp_arg->next;
	}
	return (nb);
}

char	**getarr_cmd(t_elem *arg)
{
	t_elem	*tmp_arg;
	char	**arr_cmd;
	int		i;

	arr_cmd = ft_calloc(nb_cmd(arg) + 1, sizeof(char *));
	if (!arr_cmd)
		display_error_exec("bash: ", "arr_cmd", 15);
	tmp_arg = arg;
	i = -1;
	while (tmp_arg != NULL)
	{
		arr_cmd[++i] = ft_strdup_null(tmp_arg->name);
		tmp_arg = tmp_arg->next;
	}
	return (arr_cmd);
}

int	is_valid_builtins(t_msl *ms, t_elem *arg, char **cmd_args)
{
	char	*cmd_path;
	int		path;

	if (match_multi("/usr/bin/echo", "/bin/echo", "echo", arg->name) |
		match_multi("/usr/bin/pwd", "/bin/pwd", "pwd", arg->name) |
		ft_strmatch("cd", arg->name) | ft_strmatch("unset", arg->name) |
		ft_strmatch("export", arg->name) | ft_strmatch("exit", arg->name))
		return (0);
	if (ft_strchr(cmd_args[0], '/'))
	{
		cmd_path = ft_strdup(cmd_args[0]);
		path = 1;
	}
	else
		cmd_path = get_cmd_path(ms, cmd_args[0]);
	// printf("|%s|\n", cmd_path);
	if (access(cmd_path, F_OK) == 0 && cmd_path)
		return (free(cmd_path), 0);
	if (path)
		display_error_exec("bash: ", arg->name, 2);
	else
		display_error_exec("bash: ", arg->name, 5);
	return (free(cmd_path), 1);
}

int	match_multi(char *s1, char *s2, char *s3, char *cmd)
{
	if (s1)
	{
		if (ft_strmatch(s1, cmd))
			return (1);
	}
	if (s2)
	{
		if (ft_strmatch(s2, cmd))
			return (1);
	}
	if (s3)
	{
		if (ft_strmatch(s3, cmd))
			return (1);
	}
	return (0);
}

void	builtins_execution(t_msl *ms, t_elem *arg, int use_pipe)
{
	char	**args_cmd;

	args_cmd = getarr_cmd(arg);
	ms->status = is_valid_builtins(ms, arg, args_cmd);
	if (!ms->status)
	{
		// printf("builtins %s\n", arg->name);
		if (match_multi("/usr/bin/echo", "/bin/echo", "echo", arg->name))
			ms->status = exec_echo(ms, args_cmd);
		else if (match_multi("/usr/bin/pwd", "/bin/pwd", "pwd", arg->name))		// WIP		will print ms->pwd
			ms->status = exec_pwd(ms, args_cmd);
		else if (match_multi("/usr/bin/env", "/bin/env", "env", arg->name) && use_pipe)	// DONE
			ms->status = exec_env(ms, args_cmd);
		else if (ft_strmatch("cd", arg->name))		// WIP		need update of ms->pwd and env variables PWD, OLDPWD
			ms->status = exec_cd(ms, args_cmd);
		else if (ft_strmatch("export", arg->name))	//			if successful need to update ms->arrexport and ms->arrenv
			ms->status = exec_export(ms, args_cmd);
		else if (ft_strmatch("unset", arg->name))		//			if successful need to update ms->arrexport and ms->arrenv
			ms->status = exec_unset(ms, args_cmd);
		else if (ft_strmatch("exit", arg->name))		// DONE
			exec_exit(ms, args_cmd);
	}
	ft_arrfree(args_cmd);
}

void	standard_execution(t_msl *ms, t_elem *arg)
{
	char	**args_cmd;

	args_cmd = getarr_cmd(arg);		// fix by using tmp_cmd in the structure

	// exec_one(args_cmd, ms, envp);
	execute_cmd(ms, args_cmd);
	ft_arrfree(args_cmd);
}

void	display_block(t_block *block)
{
	t_elem *tmp_arg;
	
	if (block->in)
	{
		printf("input\n");
		tmp_arg = block->in;
		while (tmp_arg != NULL)
		{
			if (tmp_arg->type == INPUT)
				printf("file : %s\n", tmp_arg->name);
			else
				printf("heredoc limiter : %s\n", tmp_arg->name);
			tmp_arg = tmp_arg->next;
		}
		printf("\n");
	}
	if (block->arg)
	{
		printf("cmd : %s\n", block->arg->name);
		tmp_arg = block->arg;
		while (tmp_arg->next != NULL)
		{
			printf("argument : %s\n", tmp_arg->next->name);
			tmp_arg = tmp_arg->next;
		}
		printf("\n");
	}
	if (block->out)
	{
		printf("output\n");
		tmp_arg = block->out;
		while (tmp_arg != NULL)
		{
			if (tmp_arg->type == TRUNC)
				printf("trunc file : %s\n", tmp_arg->name);
			else
				printf("append file : %s\n", tmp_arg->name);
			tmp_arg = tmp_arg->next;
		}
		printf("\n");
	}
}

void	write_output(t_block *block)
{
	t_elem	*tmp_arg;
	
	printf("write result into file\n");
	if (block->out)
	{
		// printf("output\n");
		tmp_arg = block->out;
		while (tmp_arg != NULL)
		{
			if (tmp_arg->type == TRUNC)
				printf("trunc file : %s\n", tmp_arg->name);
			else
				printf("append file : %s\n", tmp_arg->name);
			tmp_arg = tmp_arg->next;
		}
		printf("\n");
	}
}

void	write_input(t_block *block)
{
	t_elem	*tmp_arg;
	
	printf("input need to open and write all content as entry\n");
	if (block->in)
	{
		// printf("input\n");
		tmp_arg = block->in;
		while (tmp_arg != NULL)
		{
			if (tmp_arg->type == INPUT)
				printf("file : %s\n", tmp_arg->name);
			else
				printf("heredoc limiter : %s\n", tmp_arg->name);
			tmp_arg = tmp_arg->next;
		}
		printf("\n");
	}
}

void	execution(t_msl *ms)
{
	int	i;
	int	status;

	parsing_exec(ms);
	exec_signal();
	i = -1;
	while (ms->blocks[++i])
	{
		if (ms->blocks[i]->in)
			write_input(ms->blocks[i]);
		if (ms->blocks[i]->arg)
			exec_cmd(ms, i);
		if (ms->blocks[i]->out)
			write_output(ms->blocks[i]);
	}
	status = 0;
	i = -1;
	while (++i < ms->c_cmd)
		waitpid(ms->pid[i], &status, 0);

	// if (ms->status)
	// 	printf("status : %d\n", ms->status);
	// else
	// {
		ms->status = WEXITSTATUS(status);
		// printf("status exit : %d\n", ms->status);
	// }

	// clean all parsing
}
