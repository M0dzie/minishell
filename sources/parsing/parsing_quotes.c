/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:49:43 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/18 20:16:10 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_opened_quotes(t_msl *ms, char *input, char c)
{
	int	i;
	int	quote;

	quote = 0;
	i = -1;
	while (input[++i])
	{
		if (input[i] == c)
		{
			quote++;
			ms->lst_quote = i;
		}
	}
	if (quote % 2 != 0)
		return (1);
	return (0);
}

char	*del_quotes(t_msl *ms, char c)
{
	int		i;
	char	*new_line;
	char	**split;

	i = 0;
	new_line = ft_calloc(1, 1);
	if (!new_line)
		return (NULL);
	split = ft_split(ms->input, c);
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
		if (input[i] == 34 || input[i] == 39)
		{
			if (check_opened_quotes(ms, input, input[i]))
				return (display_errors(ms, input[i]));
			else
			{
				ms->input = del_quotes(ms, input[i]);
				input += ms->lst_quote;
			}
		}
	}
	if (ms->input[0] == '\0' || ms->input[0] == ' ')
		return (display_errors_pipe(ms, ms->input[0]));
	return (0);
}