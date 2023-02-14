/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 22:49:25 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/02/14 18:18:15 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	exit(0);
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

void	execution(t_msl *ms, char *input, char **envp)
{
	(void)input;

	char	*input_test = "/usr/bin/ls \"-l\" '-a'";
	char	*args_cmd[] = {"/usr/bin/ls", "\"-l\"", "'-a'", NULL};
	char	*input_echo = "echo \"phrase\" 'a la con'";
	char	*arr_echo[] = {"/usr/bin/echo", "'~' une phra\"se \"exemple avec \
'un vrai $PWD' qui ne s\"'\"affichera qu\"'\"entre double quote \"$PWD\"", "'", NULL};

	for (int i = 0; i <= ms->c_pipe; i++)
	{
		ft_printf("command %d : %s\n", i, ms->cmds[i][0]);
		// create_pipe(ms->cmds[i], ms, envp);
		for (int j = 1; ms->cmds[i][j]; j++)
			ft_printf("argument %d : %s\n", j, ms->cmds[i][j]);
	}
	// ft_printf("input : %s\n", ms->cmds[0][1]);

	// execute_cmd(args_cmd, &ms);
	// execute_cmd(ft_split(input_test, ' '), &ms);
	// execute_cmd(arr_echo, ms, envp);

	// create_pipe(arr_echo, ms, envp);
}
