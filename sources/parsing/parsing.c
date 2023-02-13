/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:49:26 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/13 16:29:06 by thmeyer          ###   ########.fr       */
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

void	read_prompt(char *input, char **envp, t_msl *ms)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (parsing_errors(input) == -1)
		return ;
	ms->c_pipe = count_pipes(input);
	ms->cmds = ft_calloc(ms->c_pipe + 2, sizeof(char **));
	if (!ms->cmds)
		return ;
	while (i <= ms->c_pipe)
	{
		ms->split = ft_split(input, '|');
		if (!ms->split)
			return ;
		ms->cmds[i] = ft_split(ms->split[j], ' ');
		if (!ms->cmds)
			return ;
		i++;
		j++;
	}
	print_args(ms->cmds);
	ft_arrfree(ms->split);
}

void	signal_handler(int signal)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
