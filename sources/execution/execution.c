/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:49:25 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/04/04 18:37:31 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	display_error_exec(char *first, char *second, int num_error)
{	
	char	*err[19];

	err[1] = ": invalid option";
	err[2] = ": No such file or directory";
	err[3] = ": environnement PATH not found";
	err[4] = ": environnement SHELL not found";
	err[5] = ": command not found";
	err[6] = "cannot allocate memory";
	err[7] = ": cannot create or modify: ";
	err[8] = ": environnement VARIABLES not found";
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
	if (!cmd || !cmd[0])
		return (0);
	if (match_multi("/usr/bin/echo", "/bin/echo", "echo", cmd) |
		match_multi("/usr/bin/pwd", "/bin/pwd", "pwd", cmd) |
		match_multi("/usr/bin/env", "/bin/env", "env", cmd) |
		ft_strmatch("cd", cmd) | ft_strmatch("unset", cmd) |
		ft_strmatch("export", cmd) | ft_strmatch("exit", cmd))
		return (1);
	return (0);
}

// int	nb_cmd(t_elem *arg)
// {
// 	int		nb;
// 	t_elem	*tmp_arg;

// 	nb = 0;
// 	tmp_arg = arg;
// 	while (tmp_arg != NULL)
// 	{
// 		nb++;
// 		tmp_arg = tmp_arg->next;
// 	}
// 	return (nb);
// }

// char	**getarr_cmd(t_elem *arg)
// {
// 	t_elem	*tmp_arg;
// 	char	**arr_cmd;
// 	int		i;

// 	arr_cmd = ft_calloc(nb_cmd(arg) + 1, sizeof(char *));
// 	if (!arr_cmd)
// 		display_error_exec("minishell: ", "arr_cmd", 15);
// 	tmp_arg = arg;
// 	i = -1;
// 	while (tmp_arg != NULL)
// 	{
// 		arr_cmd[++i] = ft_strdup_null(tmp_arg->name);
// 		tmp_arg = tmp_arg->next;
// 	}
// 	return (arr_cmd);
// }

int	match_multi(char *s1, char *s2, char *s3, char *cmd)
{
	if (ft_strmatch(s1, cmd) || ft_strmatch(s2, cmd) || 
	ft_strmatch(s3, cmd))
		return (1);
	return (0);
}

void	builtins_execution(t_msl *ms, t_block *block)
{
	if (match_multi("/usr/bin/echo", "/bin/echo", "echo", block->arg->name))
		ms->status = exec_echo(ms, block->args_cmd);
	else if (match_multi("/usr/bin/pwd", "/bin/pwd", "pwd", block->arg->name))
		ms->status = exec_pwd(ms, block->args_cmd);
	else if (match_multi("/usr/bin/env", "/bin/env", "env", block->arg->name))
		ms->status = exec_env(ms, block->args_cmd);
	else if (ft_strmatch("cd", block->arg->name))
		ms->status = exec_cd(ms, block->args_cmd);
	else if (ft_strmatch("export", block->arg->name))
		ms->status = exec_export(ms, block->args_cmd);
	else if (ft_strmatch("unset", block->arg->name))
		ms->status = exec_unset(ms, block->args_cmd);
	else if (ft_strmatch("exit", block->arg->name))
		exec_exit(ms, block->args_cmd);
}

// // check if heredoc as input return 1 and if heredoc is the last input return 2 else 0
// int	is_heredoc(t_block *block)
// {
// 	t_elem	*tmp_arg;
// 	int		index_here;
// 	int		index_input;

// 	index_here = 0;
// 	index_input = 0;
// 	if (block->in)
// 	{
// 		tmp_arg = block->in;
// 		while (tmp_arg != NULL)
// 		{
// 			index_input++;
// 			if (tmp_arg->type == HEREDOC)
// 				index_here = index_input;
// 			tmp_arg = tmp_arg->next;
// 		}
// 		if (index_here == index_input)
// 			return (2);
// 		else if (index_here)
// 			return (1);
// 	}
// 	return (0);
// }

// static char	*input_join(char *input, char const *buf)
// {
// 	char	*tmp_join;
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	j = 0;
// 	if (!input)
// 		tmp_join = malloc(sizeof(char) * (ft_strlen(buf) + 1));
// 	else
// 		tmp_join = malloc(sizeof(char) * (ft_strlen(input) \
// 			+ ft_strlen(buf) + 1));
// 	if (!tmp_join)
// 		return (free(tmp_join), \
// 		tmp_join = NULL, NULL);
// 	if (input)
// 	{
// 		while (input[j])
// 			tmp_join[i++] = input[j++];
// 		free(input);
// 	}
// 	j = 0;
// 	while (buf[j])
// 		tmp_join[i++] = buf[j++];
// 	tmp_join[i] = '\0';
// 	return (tmp_join);
// }

// static char	*get_input(t_block *block, t_elem *elem)
// {
// 	char	*tmp_input;

// 	block->input = NULL;
// 	tmp_input = NULL;
// 	while (ft_strmatch(tmp_input, elem->name) == 0)
// 	{
// 		tmp_input = readline("> ");
// 		if (tmp_input == 0)
// 			return (ft_putstr_fd("minishell: warning: here-document delimited by end-of-file, wanted ", 2), ft_putendl_fd(elem->name, 2), NULL);
// 		if (ft_strmatch(tmp_input, elem->name) == 0)
// 		{
// 			tmp_input = ft_strjoin(tmp_input, "\n");
// 			if (!block->input)
// 				block->input = ft_strdup(tmp_input);
// 			else
// 				block->input = input_join(block->input, tmp_input);
// 		}
// 	}
// 	return (free(tmp_input), NULL);
// }

// void	get_heredoc(t_msl *ms, t_block *block, int saveit)
// {
// 	t_elem	*tmp_arg;

// 	tmp_arg = block->in;
// 	while (tmp_arg != NULL)
// 	{
// 		if (tmp_arg->type == HEREDOC)
// 			get_input(block, tmp_arg);
// 		tmp_arg = tmp_arg->next;
// 	}
// 	if (saveit == 1)
// 		free(block->input);
// }

// int	check_input(t_msl *ms, t_block *block)
// {
// 	t_elem	*tmp_arg;
// 	int		heredoc;

// 	heredoc = is_heredoc(block);
// 	get_heredoc(ms, block, heredoc);
// 	if (block->in)
// 	{
// 		tmp_arg = block->in;
// 		while (tmp_arg != NULL)
// 		{
// 			if (block->fd_in)
// 				close (block->fd_in);
// 			if (tmp_arg->type == INPUT)
// 			{
// 				block->fd_in = open(tmp_arg->name, O_RDONLY);
// 				if (block->fd_in < 0)
// 					return (display_error_exec("minishell: ", tmp_arg->name, 2), 1);
// 			}
// 			tmp_arg = tmp_arg->next;
// 		}
// 		if (heredoc == 2)
// 			block->is_input = HEREDOC;
// 		else
// 			block->is_input = INPUT;
// 	}
// }

// int	check_output(t_msl *ms, t_block *block)
// {
// 	t_elem	*tmp_file;

// 	tmp_file = block->out;
// 	while (tmp_file != NULL)
// 	{
// 		if (tmp_file->type == TRUNC)
// 			block->fd_out = open(tmp_file->name, O_CREAT | O_RDWR | O_TRUNC, 0664);
// 		if (tmp_file->type == APPEND)
// 			block->fd_out = open(tmp_file->name, O_CREAT | O_RDWR | O_APPEND, 0664);
// 		if (block->fd_out < 0)
// 		{
// 			if (tmp_file->name[ft_strlen_null(tmp_file->name) - 1] == '/')
// 				return (display_error_exec("minishell: ", tmp_file->name, 18), 1);
// 			else if (tmp_file->name[0] == '/')
// 				return (display_error_exec("minishell: ", tmp_file->name, 13), 1);
// 			else if (ft_strchr(tmp_file->name, '/') == 0)
// 				return (display_error_exec("minishell: ", tmp_file->name, 13), 1);
// 			else
// 				return (display_error_exec("minishell: ", tmp_file->name, 2), 1);
// 		}
// 		tmp_file = tmp_file->next;
// 	}
// 	block->is_output = 1;
// 	return (0);
// }

void	execution(t_msl *ms)
{
	int	i;
	int	status;

	parsing_exec(ms);
	ft_arrfree(ms->tokens);
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
	free_exec(ms);
}
