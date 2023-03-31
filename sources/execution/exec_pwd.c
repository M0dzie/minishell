/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 21:21:14 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/03/31 14:19:00 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	invalid_pwd(char c)
{
	char	tmp_char[1];

	tmp_char[0] = c;
	display_error_exec("minishell: pwd: -", &tmp_char[0], 1);
	return (2);
}

int	exec_pwd(t_msl *ms, char **args_cmd)
{
	char	*tmp_path;
	char	**tmp_args;
	char	bufpwd[BUFSIZ];
	int		i;
	int		valid;

	valid = 0;
	// if (args_cmd[1] && args_cmd[1][0])
	if (args_cmd[1])
	{
		if (args_cmd[1][0] == '-')
		{
			if (ft_strlen(args_cmd[1]) > 2)
				valid = invalid_pwd(args_cmd[1][1]);
			else if (ft_strlen(args_cmd[1]) == 2 && args_cmd[1][1])
			{
				if (args_cmd[1][1] != '-')
					valid = invalid_pwd(args_cmd[1][1]);
			}
		}
	}
	if (valid == 0)
		printf("%s\n", getcwd(bufpwd, BUFSIZ));
	return (valid);
}
