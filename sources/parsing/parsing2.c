/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:57:28 by thmeyer           #+#    #+#             */
/*   Updated: 2023/03/01 17:14:59 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_input(char **split)
{
	int i = 0;
	int j = 0;

	while (split[i])
	{
		j = 0;
		printf("[%s][", split[i]);
		while (split[i][j])
		{
			printf("%c", split[i][j]);
			j++;
		}
		printf("]\n");
		i++;
	}
}

int	count_words(t_msl *ms)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	return (count);
}

// char	*get_words(t_msl *ms, char *input)
// {
// }

// void	read_prompt(t_msl *ms, char **envp)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	j = -1;
// 	ms->input = ft_strtrim(ms->input, " ");
// 	if (!ms->input)
// 		return ;
// 	printf("input = %s\n", ms->input);
// 	ms->split = malloc(sizeof(char *) * (count_words(ms) + 1));
// 	if (!ms->split)
// 		return (free(ms->input));
// 	while (ms->input[++i])
// 	{
// 		if (i == 0 || ms->input[i] == '\'' || ms->input[i] == '\"' \
// 		|| ms->input[i] == '|' || ms->input[i] == '>' || ms->input[i] == '<')
// 		{
// 			ms->split = ms->input[i];
// 			ms->split[++j] = get_word(ms, ms->input + i);
// 			i = ms->end_of_word;
// 		}
// 	}
// 	print_input(ms->split);
// 	free(ms->input);
// }

/*
input = salut "a tous" hola | < $HOME '   dd wdw ' cd ls
[ ][salut]
["][a tous]
[|][|]
[<][<]
[ ][$HOME]
['][   dd wdw  ]
[ ][cd]
[ ][ls]
*/