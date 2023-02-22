/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:38:38 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/02/22 22:12:00 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/minimehdi.h"

int	is_env(char *arg)
{
	if (ft_strlen(arg) != 3)
		return (0);
	if (!(arg[0] == 'e' && arg[1] == 'n' && arg[2] == 'v'))
		return (0);
	return (1);
}

int	first_invalid(char *arg)
{
	char 	*invalid;
	int		i;

	invalid = "./~`";
	i = -1;
	while (invalid[++i])
	{
		if (arg[0] == invalid[i])
			return (display_error_exec("env: '", arg, 13), -1);
	}
	return (0);
}

int	cmd_valid(t_msl *ms, char **arg)
{
	char	**env;
	char	**tmp_paths;
	char	*join_one;
	char	*join_two;
	int		i;

	i = -1;
	env = ft_getenv(ms);
	tmp_paths = ft_split(getenv("PATH"), ':');
	while (tmp_paths[++i])
	{
		join_one = ft_strjoin(tmp_paths[i], "/");
		join_two = ft_strjoin(join_one, arg[0]);
		if (access(join_two, F_OK) == 0)
			return (pipe_one(arg, ms, env), 1);
		free(join_one);
		free(join_two);
	}
	return (ft_arrfree(tmp_paths), 0);
}

void	exec_env(t_msl *ms, char **args_cmd, char **envp)
{	
	int	nb_args;
	int	i;

	nb_args = ft_arrlen(args_cmd);
	if (nb_args > 1)
	{
		i = 0;
		while (args_cmd[++i])
		{
			if (!is_env(args_cmd[i]))
			{
				if (first_invalid(args_cmd[i]))
					return ;
				else if (cmd_valid(ms, args_cmd + i))
					return ;
				else
				{
					display_error_exec("env: ", args_cmd[i], 2);
					return ;
				}
			}
		}
	}
	display_env(ms);
}
