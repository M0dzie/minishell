/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:49:25 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/04/05 01:50:51 by mehdisapin       ###   ########.fr       */
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
