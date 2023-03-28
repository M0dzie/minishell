/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:49:25 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/03/28 15:42:19 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <errno.h>
#include <stdlib.h>

int	display_error_exec(char *first, char *second, int num_error)
{	
	char	*err[19];		// to correct

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
	err[17] = " not set";
	err[18] = ": Is a directory";
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
	int		path;
	int		isdir;

	path = 0;
	isdir = 0;
	if (ft_strchr(cmd_args[0], '/'))
	{
		cmd_path = ft_strdup(cmd_args[0]);
		if (access(cmd_path, F_OK) == 0)
			isdir = 1;
		path = 1;
	}
	else
		cmd_path = get_cmd_path(ms, cmd_args[0]);
	execve(cmd_path, cmd_args, ms->arrenv);
	free(cmd_path);
	if (!getvar(ms, "PATH"))
		display_error_exec("minishell: ", cmd_args[0], 2);
	else if (path)
	{
		if (isdir)
			display_error_exec("minishell: ", cmd_args[0], 18);
		else
			display_error_exec("minishell: ", cmd_args[0], 2);
	}
	else
		display_error_exec("minishell: ", cmd_args[0], 5);
	ft_arrfree(cmd_args);
	if (isdir)
		exit (126);
	exit (127);
}

int	is_builtins(char *cmd)
{
	char	*tmp_cmd;
	char	**tmp_split;

	if (!cmd || !cmd[0])
		return (0);
	if (match_multi("/usr/bin/echo", "/bin/echo", "echo", cmd) |
		match_multi("/usr/bin/pwd", "/bin/pwd", "pwd", cmd) |
		ft_strmatch("cd", cmd) | ft_strmatch("unset", cmd) |
		ft_strmatch("export", cmd) | ft_strmatch("exit", cmd))
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
		display_error_exec("minishell: ", "arr_cmd", 15);
	tmp_arg = arg;
	i = -1;
	while (tmp_arg != NULL)
	{
		arr_cmd[++i] = ft_strdup_null(tmp_arg->name);
		tmp_arg = tmp_arg->next;
	}
	return (arr_cmd);
}

int	match_multi(char *s1, char *s2, char *s3, char *cmd)
{
	if (ft_strmatch(s1, cmd) || ft_strmatch(s2, cmd) || 
	ft_strmatch(s3, cmd))
		return (1);
	return (0);
}

void	builtins_execution(t_msl *ms, t_elem *arg, int use_pipe)	// remove use_pipe
{
	char	**args_cmd;

	args_cmd = getarr_cmd(arg);
	if (match_multi("/usr/bin/echo", "/bin/echo", "echo", arg->name))
		ms->status = exec_echo(ms, args_cmd);
	else if (match_multi("/usr/bin/pwd", "/bin/pwd", "pwd", arg->name))		// WIP		will print ms->pwd
		ms->status = exec_pwd(ms, args_cmd);
	// else if (match_multi("/usr/bin/env", "/bin/env", "env", arg->name) && use_pipe)	// DONE
	else if (match_multi("/usr/bin/env", "/bin/env", "env", arg->name))	// DONE
		ms->status = exec_env(ms, args_cmd);
	else if (ft_strmatch("cd", arg->name))		// WIP		need update of ms->pwd and env variables PWD, OLDPWD
		ms->status = exec_cd(ms, args_cmd);
	else if (ft_strmatch("export", arg->name))	//			if successful need to update ms->arrexport and ms->arrenv
		ms->status = exec_export(ms, args_cmd);
	else if (ft_strmatch("unset", arg->name))		//			if successful need to update ms->arrexport and ms->arrenv
		ms->status = exec_unset(ms, args_cmd);
	else if (ft_strmatch("exit", arg->name))		// DONE
		exec_exit(ms, args_cmd);
	ft_arrfree(args_cmd);
}

void	standard_execution(t_msl *ms, t_elem *arg)
{
	char	**args_cmd;

	args_cmd = getarr_cmd(arg);		// fix by using tmp_cmd in the structure
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

// check if heredoc as input return 1 and if heredoc il the last input return 2 else 0
int	is_heredoc(t_block *block)
{
	t_elem	*tmp_arg;
	int		index_here;
	int		index_input;

	index_here = 0;
	index_input = 0;
	if (block->in)
	{
		tmp_arg = block->in;
		while (tmp_arg != NULL)
		{
			index_input++;
			if (tmp_arg->type == HEREDOC)
				index_here = index_input;
			tmp_arg = tmp_arg->next;
		}
		if (index_here == index_input)
			return (2);
		else if (index_here)
			return (1);
	}
	return (0);
}

char	*get_heredoc(t_block *block, int saveit)
{
	if (saveit == 1)
		// loop to simulate getting input but not saving it
		printf("Simulate here_doc\n");
	else if (saveit == 2)
		printf("Save here_doc\n");
		// adding input into string and returning it
	return (NULL);
}

int	check_input(t_msl *ms, t_block *block)
{
	t_elem	*tmp_arg;
	int		heredoc;

	heredoc = is_heredoc(block);
	get_heredoc(block, heredoc);
	if (block->in)
	{
		tmp_arg = block->in;
		while (tmp_arg != NULL)
		{
			if (block->fd_in)
				close (block->fd_in);
			if (tmp_arg->type == INPUT)
			{
				block->fd_in = open(tmp_arg->name, O_RDONLY);
				if (block->fd_in < 0)
					return (display_error_exec("minishell: ", tmp_arg->name, 2), 1);
			}
			tmp_arg = tmp_arg->next;
		}
		if (heredoc == 2)
			block->is_input = HEREDOC;
		else
			block->is_input = INPUT;
	}
	return (0);
}

int	check_output(t_msl *ms, t_block *block)
{
	t_elem	*tmp_file;

	tmp_file = block->out;
	while (tmp_file != NULL)
	{
		if (tmp_file->type == TRUNC)
			block->fd_out = open(tmp_file->name, O_CREAT | O_RDWR | O_TRUNC, 0664);
		if (tmp_file->type == APPEND)
			block->fd_out = open(tmp_file->name, O_CREAT | O_RDWR | O_APPEND, 0664);
		if (block->fd_out < 0)
		{
			if (tmp_file->name[ft_strlen_null(tmp_file->name) - 1] == '/')
				return (display_error_exec("minishell: ", tmp_file->name, 18), 1);
			else if (tmp_file->name[0] == '/')
				return (display_error_exec("minishell: ", tmp_file->name, 13), 1);
			else if (ft_strchr(tmp_file->name, '/') == 0)
				return (display_error_exec("minishell: ", tmp_file->name, 13), 1);
			else
				return (display_error_exec("minishell: ", tmp_file->name, 2), 1);
		}
		close(block->fd_out);
		tmp_file = tmp_file->next;
	}
	return (0);
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
		check_input(ms, ms->blocks[i]);
		if (ms->blocks[i]->out)
			check_output(ms, ms->blocks[i]);
		exec_cmd(ms, i);
	}
	status = 0;
	i = -1;
	while (++i < ms->c_cmd)
		waitpid(ms->pid[i], &status, 0);
	ms->status = WEXITSTATUS(status);
	// clean all parsing
}
