/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:49:26 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/21 14:46:07 by msapin           ###   ########.fr       */
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

	i = -1;
	ms->input = ft_strtrim(ms->input, " ");
	if (ms->input[0] == '\0' || parsing_quotes(ms) == -1 || \
	parsing_errors(ms) == -1)
		return (free(ms->input));
	// if (ft_strncmp(ms->input, "echo", 4) == 0)
	// 	return (parsing_echo(ms));
	ms->c_pipe = count_pipes(ms->input);
	ms->c_cmd = count_pipes(ms->input) + 1;
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
	execution(ms, ms->input, envp);
}
