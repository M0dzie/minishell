/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 21:21:14 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/02/23 14:01:14 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	invalid_pwd(char c)
{
	display_error_exec("bash: pwd: -", &c, 1);
	return (2);
}

int	exec_pwd(t_msl *ms, char **args_cmd, char **envp)
{
	char	*tmp_path;
	char	**tmp_args;
	int		i;
	int		valid;

	tmp_path = get_cmd_path(args_cmd[0], envp);
	tmp_args = ft_calloc(1, sizeof(char *));
	tmp_args = ft_arradd_back(tmp_args, tmp_path);
	valid = 0;
	if (args_cmd[1])
	{
		if (args_cmd[1][0] == '-')
		{
			if (ft_strlen(args_cmd[1]) > 2)
				valid = invalid_pwd(args_cmd[1][1]);
			else if (ft_strlen(args_cmd[1]) == 2)
			{
				if (args_cmd[1][1] != '-')
					valid = invalid_pwd(args_cmd[1][1]);
			}
		}
	}
	if (valid == 0)
		handle_cmd(ms, tmp_args, envp);
	return (valid);
}
