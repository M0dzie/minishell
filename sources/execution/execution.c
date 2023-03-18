/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:49:25 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/03/18 11:44:31 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <errno.h>
#include <stdlib.h>

int	display_error_exec(char *first, char *second, int num_error)
{	
	char	*err[16];		// to correct

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

void	execute_cmd(t_msl *ms, char **cmd_args, char **envp)
{
	char	*cmd_path;

	if (ft_strchr(cmd_args[0], '/'))
		cmd_path = ft_strdup(cmd_args[0]);
	else
		cmd_path = get_cmd_path(cmd_args[0], envp);
	execve(cmd_path, cmd_args, envp);
	display_error_exec("bash: ", cmd_args[0], 5);
	free(cmd_path);

	// error message

	// ft_arrfree(cmd_args);
	// exit(127);
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
		execute_cmd(ms, args_cmd, envp);
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
		execute_cmd(ms, args_cmd, envp);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		// wait(NULL);
		// waitpid(pid, &rtn, 0);
	}
}

int	strict_cmp(const char *builts, const char *cmd)
{
	size_t	i;
	size_t	cmd_len;

	i = -1;
	if (!builts || !cmd)
		return (0);
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

	if (!cmd || !cmd[0])
		return (0);
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

void	builtins_execution(t_msl *ms, t_elem *arg)
{
	char	**envp;
	char	**args_cmd;

	envp = ft_getenv(ms, 0);
	args_cmd = getarr_cmd(arg);
	if (strict_cmp("echo", arg->name))
		exec_echo(ms, args_cmd, envp);
	else if (strict_cmp("pwd", args_cmd[0]))		// DONE
		ms->status = exec_pwd(ms, args_cmd, envp);
	else if (strict_cmp("env", args_cmd[0]))
		ms->status = exec_env(ms, args_cmd, envp);
	else if (strict_cmp("cd", args_cmd[0]))		// WIP
		exec_cd(ms, args_cmd, envp);
	else if (strict_cmp("export", args_cmd[0]))
		ms->status = exec_export(ms, args_cmd, envp);
	else if (strict_cmp("unset", args_cmd[0]))
		ms->status = exec_unset(ms, args_cmd, envp);
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

void	standard_execution(t_msl *ms, t_elem *arg)
{
	char	**envp;
	char	**args_cmd;

	envp = ft_getenv(ms, 0);
	args_cmd = getarr_cmd(arg);
	// execute_cmd(ms, args_cmd, envp);
	// handle_cmd(ms, args_cmd, envp);
	// pipe_one(args_cmd, ms, envp);
	execute_cmd(ms, args_cmd, envp);
}

int	is_file(t_msl *ms, int index)
{
	if (index > 0 && ms->tokens[index - 1])
	{
		if (strict_cmp(ms->tokens[index - 1], "<"))
		{
			if (access(ms->tokens[index], F_OK))
				printf("invalid file %s\n", ms->tokens[index]);
			return (1);
		}
		else if (strict_cmp(ms->tokens[index - 1], ">") || strict_cmp(ms->tokens[index - 1], ">>"))
			return (1);
	}
	return (0);
}

int	is_redir(t_msl *ms, int index)
{
	if (strict_cmp(ms->tokens[index], "<") || strict_cmp(ms->tokens[index], "<<")
	|| strict_cmp(ms->tokens[index], ">") || strict_cmp(ms->tokens[index], ">>"))
		return (1);
	return (0);
}

void	pipe_malloc(t_msl *ms)
{
	int	i;

	i = 0;
	ms->pipes = ft_calloc(ms->c_pipe + 1, sizeof(int *));
	if (!ms->pipes)
		display_error_exec("bash: ", "pipes", 15);
	while (i < ms->c_pipe)
	{
		ms->pipes[i] = ft_calloc(2, sizeof(int));
		if (!ms->pipes[i])
			display_error_exec("bash: ", "pipex[i]", 15);
		pipe(ms->pipes[i]);
		i++;
	}
}

void	parsing_pipex(t_msl *ms)
{
	ms->pid = ft_calloc(ms->c_cmd + 1, sizeof(pid_t));
	if (!ms->pid)
		display_error_exec("bash: ", "pid", 15);
	if (ms->c_pipe > 0)
		pipe_malloc(ms);
}

void	elem_addback(t_elem **stack, t_elem *new_elem)
{
	t_elem	*addback;

	if (!(*stack))
		*stack = new_elem;
	else
	{
		addback = (*stack);
		while (addback->next != NULL)
			addback = addback->next;
		addback->next = new_elem;
	}
}

t_elem	*new_elem(char *name, int type)
{
	t_elem	*new_elem;

	new_elem = malloc(sizeof(t_elem));
	if (!new_elem)
		return (display_error_exec("bash: ", "new_elem", 15), NULL);
	new_elem->name = ft_strdup_null(name);
	new_elem->type = type;
	new_elem->next = NULL;
	return (new_elem);
}

void	malloc_blocks(t_msl *ms)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i <= ms->c_pipe)
	{
		while (ms->tokens[++j])
		{
			if (strict_cmp(ms->tokens[j], "|"))
				break;
			else if (strict_cmp(ms->tokens[j], "<") && ms->tokens[j + 1])
				elem_addback(&ms->blocks[i]->in, new_elem(ms->tokens[++j], INPUT));
			else if (strict_cmp(ms->tokens[j], "<<") && ms->tokens[j + 1])
				elem_addback(&ms->blocks[i]->in, new_elem(ms->tokens[++j], HEREDOC));
			else if (strict_cmp(ms->tokens[j], ">") && ms->tokens[j + 1])
				elem_addback(&ms->blocks[i]->out, new_elem(ms->tokens[++j], TRUNC));
			else if (strict_cmp(ms->tokens[j], ">>") && ms->tokens[j + 1])
				elem_addback(&ms->blocks[i]->out, new_elem(ms->tokens[++j], APPEND));
			else if (!ms->blocks[i]->cmd_found)
			{
				elem_addback(&ms->blocks[i]->arg, new_elem(ms->tokens[j], CMD));
				ms->blocks[i]->cmd_found = 1;
			}
			else
				elem_addback(&ms->blocks[i]->arg, new_elem(ms->tokens[j], ARG));
		}
	}
}

void	malloc_pipe(t_msl *ms)
{
	int	i;

	i = 0;
	ms->pipes = ft_calloc(ms->c_pipe, sizeof(int *));
	if (!ms->pipes)
		display_error_exec("bash: ", "pipes", 15);
	while (i < ms->c_pipe)
	{
		ms->pipes[i] = ft_calloc(2, sizeof(int));
		if (!ms->pipes[i])
			display_error_exec("bash: ", "pipex[i]", 15);
		pipe(ms->pipes[i]);
		i++;
	}
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

void	parsing_exec(t_msl *ms)
{
	int	i;
	int	j;

	ms->blocks = ft_calloc(ms->c_pipe + 2, sizeof(t_block *));
	if (!ms->blocks)
		display_error_exec("bash: ", "ms->blocks", 15);
	i = -1;
	j = -1;
	while (++i <= ms->c_pipe)
	{
		ms->blocks[i] = malloc(sizeof(t_block));
		if (!ms->blocks[i])
			display_error_exec("bash: ", "ms->blocks[i]", 15);
		ms->blocks[i]->arg = NULL;
		ms->blocks[i]->in = NULL;
		ms->blocks[i]->out = NULL;
		ms->blocks[i]->input = NULL;
		ms->blocks[i]->index = i;
		ms->blocks[i]->cmd_found = 0;
	}
	ms->pid = ft_calloc(ms->c_cmd, sizeof(pid_t));
	if (!ms->pid)
		display_error_exec("bash: ", "pid", 15);
	malloc_pipe(ms);
	malloc_blocks(ms);
}

void	write_output(t_block *block)
{
	t_elem	*tmp_arg;
	
	printf("write result into file\n");
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

void	exec_last_cmd(t_msl *ms, int index)
{
	printf("last block - cmd : %s\n", ms->blocks[index]->arg->name);

	ms->pid[ms->c_pipe - 1] = fork();
	if (ms->pid[ms->c_pipe - 1] < 0)
		display_error_exec("bash: ", "fork", 15);
	else if (ms->pid[ms->c_pipe - 1] == 0)
	{
		close(ms->pipes[ms->c_pipe - 1][1]);
		dup2(ms->pipes[ms->c_pipe - 1][0], STDIN_FILENO);
		close(ms->pipes[ms->c_pipe - 1][0]);
		// if (pipex->outfile < 0)
		// {
		// 	free_pipex(pipex);
		// 	exit (1);
		// }
		// dup2(pipex->outfile, STDOUT_FILENO);
		// close(pipex->outfile);
		// execute_cmd(pipex, args[pipex->nb_args - 2], envp);
		if (ms->blocks[index]->arg)
		{
			if (is_builtins(ms->blocks[index]->arg->name))
				builtins_execution(ms, ms->blocks[index]->arg);
			else
				standard_execution(ms, ms->blocks[index]->arg);
		}
	}
	else
	{
		// if (pipex->outfile > 0)
		// 	close(pipex->outfile);
		close(ms->pipes[ms->c_pipe - 1][0]);
	}
}

void	exec_middle_cmd(t_msl *ms, int index)
{
	printf("middle block - cmd : %s\n", ms->blocks[index]->arg->name);
	// pipex->pid[i] = fork();
	// if (pipex->pid[i] < 0)
	// 	display_error("bash: ", "fork", 5);
	// else if (pipex->pid[i] == 0)
	// {
	// 	close(pipex->pipes[i][0]);
	// 	dup2(pipex->pipes[i - 1][0], STDIN_FILENO);
	// 	close(pipex->pipes[i - 1][0]);
	// 	dup2(pipex->pipes[i][1], STDOUT_FILENO);
	// 	close(pipex->pipes[i][1]);
	// 	execute_cmd(pipex, args[0], envp);
	// }
	// else
	// {
	// 	close(pipex->pipes[i - 1][0]);
	// 	close(pipex->pipes[i][1]);
	// }
}

void	exec_first_cmd(t_msl *ms, int index)
{
	printf("first block - cmd : %s\n", ms->blocks[index]->arg->name);
	ms->pid[0] = fork();
	if (ms->pid[0] < 0)
		display_error_exec("bash: ", "fork", 15);
	else if (ms->pid[0] == 0)
	{
		close(ms->pipes[0][0]);
		dup2(ms->pipes[0][1], STDOUT_FILENO);
		close(ms->pipes[0][1]);
		// if (pipex->infile < 0)
		// {
		// 	free_pipex(pipex);
		// 	exit (1);
		// }
		// handle_input(pipex, 0);
		// execute_cmd(pipex, args[index], envp);
		if (ms->blocks[index]->arg)
		{
			if (is_builtins(ms->blocks[index]->arg->name))
				builtins_execution(ms, ms->blocks[index]->arg);
			else
				standard_execution(ms, ms->blocks[index]->arg);
		}
	}
	else
	{
		// handle_input(pipex, 1);
		close(ms->pipes[0][1]);
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

void	exec_cmd(t_msl *ms, int i)
{
	if (ms->c_cmd == 1)
		// printf("only one block - cmd : %s\n", ms->blocks[i]->arg->name);
		exec_first_cmd(ms, i);
	else if (i == 0)
		exec_first_cmd(ms, i);
	else if (i == ms->c_cmd - 1)
		// printf("last block - cmd : %s\n", ms->blocks[i]->arg->name);
		exec_last_cmd(ms, i);
	else
		exec_middle_cmd(ms, i);
}

void	execution(t_msl *ms)
{
	int	i;
	int	status;

	parsing_exec(ms);
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
}
