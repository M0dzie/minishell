/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:49:26 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/13 14:33:55 by thmeyer          ###   ########.fr       */
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

void	read_prompt(char *input, char **envp)
{
	int		i;
	int		j;
	int		c_pipe;
	char	**split;
	char	***args;

	i = 0;
	j = 0;
	c_pipe = count_pipes(input);
	args = ft_calloc(c_pipe + 2, sizeof(char **));
	if (!args)
		return ;
	while (i <= c_pipe)
	{
		split = ft_split(input, '|');
		if (!split)
			return ;
		args[i] = ft_split(split[j], ' ');
		if (!args)
			return ;
		i++;
		j++;
	}
	print_args(args);
	free(split);
}

void	signal_handler(int signal)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
