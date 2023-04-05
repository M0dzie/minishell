/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:46:45 by msapin            #+#    #+#             */
/*   Updated: 2023/04/05 01:18:04 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*get_cmd_path(t_msl *ms, char *cmd)
{
	char	**tmp_paths;
	char	*join_one;
	char	*join_two;
	int		i;
	t_var	*tmp;

	i = -1;
	tmp = getvar(ms, "PATH");
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

void	display_error_cmd(t_msl *ms, char **cmd_args, int path, int isdir)
{
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
	display_error_cmd(ms, cmd_args, path, isdir);
	ft_arrfree(cmd_args);
	if (isdir)
		exit (126);
	exit (127);
}
