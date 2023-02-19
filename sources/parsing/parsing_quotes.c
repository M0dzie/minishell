/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:49:43 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/19 17:45:22 by thmeyer          ###   ########.fr       */
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

char	*del_quotes(char *input, char c)
{
	int		i;
	char	*new_line;
	char	**split;

	i = 0;
	new_line = ft_calloc(1, 1);
	if (!new_line)
		return (NULL);
	split = ft_split(input, c);
	if (!split)
		return (NULL);
	while (split[i])
	{
		new_line = ft_strjoin(new_line, split[i]);
		if (!new_line)
			return (NULL);
		i++;
	}
	ft_arrfree(split);
	printf("%s\n", new_line);
	return (new_line);
}

int	parsing_quotes(t_msl *ms)
{
	int		i;
	char	*input;

	i = -1;
	input = ms->input;
	while (input[++i])
	{
		printf("%d = %s\n", i, input + i);
		if (input[i] == 34 || input[i] == 39)
		{
			if (check_opened_quotes(ms, input, i, input[i]))
				return (display_errors(ms, input[i]));
			input = del_quotes(input, input[i]);
			i = ms->lst_quote - 2;
		}
	}
	ms->input = input;
	if (ms->input[0] == '\0' || ms->input[0] == ' ')
		return (display_errors_pipe(ms, ms->input[0]));
	return (0);
}