/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:49:43 by thmeyer           #+#    #+#             */
/*   Updated: 2023/03/03 16:41:32 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_opened_quotes(t_msl *ms, int i, char quote)
{
	if (ms->input[i] == '\0')
		return (1);
	while (ms->input[i] && ms->input[i] != quote)
		i++;
	if (ms->input[i] == quote)
		return (ms->lst_quote = i, 0);
	return (1);
}

char	*parsing_quotes_split(t_msl *ms, char *split)
{
	int		i;

	i = -1;
	while (split[++i])
	{
		if (split[i] == '\'' || split[i] == '\"')
		{
			check_opened_quotes(ms, i + 1, ms->input[i]);
			split = del_quotes(split, i, ms->lst_quote + 1, \
			split[i]);
			if (!split)
				return (NULL);
			i = ms->lst_quote - 2;
		}
	}
	return (split);
}

int	parsing_quotes(t_msl *ms)
{
	int		i;

	i = -1;
	while (ms->input[++i])
	{
		if (ms->input[i] == '\'' || ms->input[i] == '\"')
		{
			if (check_opened_quotes(ms, i + 1, ms->input[i]))
				return (display_errors(ms, ms->input, ms->input[i]));
			i = ms->lst_quote;
		}
	}
	// if (ms->input[0] == '\0' || ms->input[0] == ' ')
	// 	return (display_errors_pipe(ms, ms->input, ms->input[0]));
	return (0);
}
