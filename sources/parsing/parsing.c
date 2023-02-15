/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:49:26 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/15 11:39:21 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_args(char ***args)
{
	int i = 0;
	int j = 0;

	while (args[i])
	{
		printf("args[%d]\n", i);
		j = 0;
		while (args[i][j])
			printf("%s\n", args[i][j++]);
		i++;
	}
}

int	count_pipes(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '|')
			count++;
		i++;
	}
	return (count);
}

void	read_prompt(t_msl *ms, char **envp)
{
	int		i;

	i = 0;
	// if (ft_strncmp(ms->input, "echo", 4) == 0)
	// 	parsing_errors_echo(ms); + else
	if (parsing_errors(ms) == -1 || ms->input[i] == '\0')
		return ;
	ms->c_pipe = count_pipes(ms->input);
	ms->cmds = ft_calloc(ms->c_pipe + 2, sizeof(char **));
	if (!ms->cmds)
		return ;
	while (i <= ms->c_pipe)
	{
		ms->split = ft_split(ms->input, '|');
		if (!ms->split)
			return ;
		ms->cmds[i] = ft_split(ms->split[i], ' ');
		if (!ms->cmds)
			return ;
		i++;
	}
	print_args(ms->cmds);
	ft_arrfree(ms->split);
}
