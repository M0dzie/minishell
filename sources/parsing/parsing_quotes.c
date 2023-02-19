/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:49:43 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/19 18:30:16 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_opened_quotes(t_msl *ms, char *input, int i, char c)
{
	int	quote;

	quote = 0;
	while (input[i])
	{
		if (input[i] == c)
		{
			quote++;
			ms->lst_quote = i;
		}
		i++;
	}
	if (quote % 2 != 0)
		return (1);
	return (0);
}

char	*get_old_line(char *input, int index)
{
	int		i;
	char	*old_line;

	i = -1;
	old_line = malloc(sizeof(char) * index + 1);
	if (!old_line)
		return (NULL);
	while (++i < index)
		old_line[i] = input[i];
	old_line[i] = '\0';
	return (old_line);
}

char	*del_quotes(char *input, int index, char c)
{
	int		i;
	char	*old_line;
	char	*new_line;
	char	**split;

	i = -1;
	old_line = get_old_line(input, index);
	new_line = ft_calloc(1, 1);
	split = ft_split(input + index, c);
	if (!new_line || !old_line || !split)
		return (NULL);
	while (split[++i])
	{
		new_line = ft_strjoin(new_line, split[i]);
		if (!new_line)
			return (NULL);
	}
	ft_arrfree(split);
	new_line = ft_strjoin(old_line, new_line);
	if (!new_line)
		return (NULL);
	printf("new_line = %s\n", new_line);
	return (free(old_line), new_line);
}

int	parsing_quotes(t_msl *ms)
{
	int		i;
	char	*input;

	i = -1;
	input = ms->input;
	while (input[++i])
	{
		if (input[i] == 34 || input[i] == 39)
		{
			if (check_opened_quotes(ms, input, i, input[i]))
				return (display_errors(ms, input[i]));
			input = del_quotes(input, i, input[i]);
			i = ms->lst_quote - 2;
		}
	}
	ms->input = input;
	if (ms->input[0] == '\0' || ms->input[0] == ' ')
		return (display_errors_pipe(ms, ms->input[0]));
	return (0);
}