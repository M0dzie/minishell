/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 21:55:22 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/27 10:52:14 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//ne pas oublier d'envoyer tous les espaces donc ne pas split ' '

void	parsing_echo(t_msl *ms, char *input, char **envp)
{
	int	i;

	i = -1;
	printf("ms->input = %s\n", ms->input);
	printf("input = %s\n", input);
	ms->cmds = ft_calloc(ms->c_pipe + 2, sizeof(char **));
	if (!ms->cmds)
		return ;
	while (++i <= ms->c_pipe)
	{
		ms->split = ft_split(ms->input, '|');
		if (!ms->split)
			return ;
		ms->cmds[i] = ft_split(ms->split[i], ' ');
		if (!ms->cmds)
			return ;
	}
	ft_arrfree(ms->split);
	print_args(ms->cmds);
	// execution(ms, ms->input, envp);
}
