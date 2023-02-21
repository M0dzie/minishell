/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:38:38 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/02/21 09:39:09 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_env(t_msl *ms, char **args_cmd, char **envp)
{	
	int	i;

	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
	printf("\n");
	create_pipe(args_cmd, ms, envp);
}
