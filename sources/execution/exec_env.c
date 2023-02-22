/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:38:38 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/02/22 18:57:51 by msapin           ###   ########.fr       */
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

int	cmd_valid(char **arg)
{
	printf("%s\n", arg[0]);
	char	**tmp_paths;
	char	*join_one;
	char	*join_two;
	int		i;

	i = -1;
	tmp_paths = ft_split(getenv("PATH"), ':');
	while (tmp_paths[++i])
	{
		join_one = ft_strjoin(tmp_paths[i], "/");
		join_two = ft_strjoin(join_one, arg[0]);
		if (access(join_two, F_OK) == 0)
			return (printf("cmd valid\n"), 1);			/// execute command
		free(join_one);
		free(join_two);
	}
	return (printf("cmd invalid\n"), ft_arrfree(tmp_paths), 0);
}

void	exec_env(t_msl *ms, char **args_cmd, char **envp)
{	
	// int	i;

	// i = -1;
	// while (envp[++i])
	// 	printf("%s\n", envp[i]);
	// printf("\n");
	// create_pipe(args_cmd, ms, envp);
	// handle_cmd(ms, args_cmd, envp);
	int	valid;
	int	nb_args;
	int	i;

	valid = 1;
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
				else if (cmd_valid(args_cmd + i))
					return ;
				else
				{
					display_error_exec("env: ", args_cmd[i], 2);
					return ;
				}
				// printf("%s is not env\n", args_cmd[i]);
				// valid = 0;
			}
		}
		// printf("multiple args\n");
	}
	if (valid)
		display_env(ms);
}
