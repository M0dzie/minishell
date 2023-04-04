/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:49:43 by thmeyer           #+#    #+#             */
/*   Updated: 2023/04/04 11:02:25 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_sign(char *token, int i)
{
	while (token[i] && token[i] != '\"')
	{
		if (token[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	check_opened_quotes(t_msl *ms, char *input, int i, char quote)
{
	if (!input)
		return (1);
	while (input[i] && input[i] != quote)
		i++;
	if (input[i] == quote)
		return (ms->lst_delim = i, 0);
	return (1);
}

char	*parsing_env_var(t_msl *ms, char *input)
{
	int		i;
	int		in_dquote;

	i = -1;
	in_dquote = 0;
	while (input[++i])
	{
		if (input[i] == '\'' && !check_opened_quotes(ms, input, i + 1, '\'') \
		&& !in_dquote)
			i = ms->lst_delim;
		if (input[i] == '$' || input[i] == '\"')
		{
			if (input[i] == '\"')
				in_dquote = !in_dquote;
			if (input[i] == '$' || (in_dquote && check_sign(input, i + 1)))
			{
				input = switch_var(ms, input, i);
				if (!input)
					return (NULL);
				i = ms->fst_delim;
			}
		}
	}
	return (input);
}

char	*parsing_quotes_split(t_msl *ms, char *token)
{
	int	i;

	i = -1;
	while (token[++i])
	{
		if (token[i] == '\'' || token[i] == '\"')
		{
			if (!check_opened_quotes(ms, token, i + 1, token[i]))
			{
				token = del_quotes(token, i, ms->lst_delim + 1, \
				token[i]);
				if (!token)
					return (NULL);
				i = ms->lst_delim - 2;
			}
		}
	}
	return (token);
}

int	parsing_quotes(t_msl *ms)
{
	int		i;

	i = -1;
	while (ms->input[++i])
	{
		if (ms->input[i] == '\'' || ms->input[i] == '\"')
		{
			if (check_opened_quotes(ms, ms->input, i + 1, ms->input[i]))
				return (display_errors(ms, ms->input, ms->input[i]));
			i = ms->lst_delim;
		}
	}
	return (0);
}
