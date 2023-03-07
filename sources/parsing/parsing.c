/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:49:26 by thmeyer           #+#    #+#             */
/*   Updated: 2023/03/06 17:22:04 by thmeyer          ###   ########.fr       */
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

void	count_pipes(t_msl *ms)
{
	int	i;

	i = 0;
	ms->c_pipe = 0;
	while (ms->input[i])
	{
		if (ms->input[i] == '|')
			ms->c_pipe++;
		i++;
	}
	ms->c_cmd = ms->c_pipe + 1;
}

void	read_prompt(t_msl *ms, char **envp)
{
	int		i;

	i = -1;
	ms->input = ft_strtrim(ms->input, " ");
	count_pipes(ms);
	if (ms->input[0] == '\0' || parsing_errors(ms, ms->input, \
	ms->c_pipe) == -1 || parsing_quotes(ms) == -1)
		return (free(ms->input));
	ms->cmds = ft_calloc(ms->c_pipe + 2, sizeof(char **));
	if (!ms->cmds)
		return (free(ms->input));
	while (++i <= ms->c_pipe)
	{
		ms->split = ft_split(ms->input, '|');
		if (!ms->split)
			return (free(ms->input));
		ms->cmds[i] = ms_split(ms, ms->split[i]);
		if (!ms->cmds)
			return (free(ms->input), ft_arrfree(ms->split));
	}
	ft_arrfree(ms->split);
	print_args(ms->cmds);
	execution(ms, ms->input, envp);
}
