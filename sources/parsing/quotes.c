/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:49:43 by thmeyer           #+#    #+#             */
/*   Updated: 2023/03/08 15:42:57 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_opened_quotes(t_msl *ms, char *input, int i, char quote)
{
	if (input[i] == '\0')
		return (1);
	while (input[i] && input[i] != quote)
		i++;
	if (input[i] == quote)
		return (ms->lst_quote = i, 0);
	return (1);
}

char	*parsing_env_var(t_msl *ms, char *token)
{
	int	i;

	i = -1;
	while (token[++i])
	{
		if (token[i] == '\'' && !check_opened_quotes(ms, token, i, '\''))
			i = ms->lst_quote;
		if (token[i] == '$' || (token[i] == '\"' && check_sign(token, i + 1)))
		{
			token = switch_var(ms, token, i);
			if (!token)
				return (NULL);
			printf("new token = %s\n", token);
		}
		// if (check_sign(token, 0))
		// 	parsing_env_var(ms, token);
	}
	return (token);
}

char	*parsing_quotes_split(t_msl *ms, char *token)
{
	int	i;

	i = -1;
	token = parsing_env_var(ms, token);
	if (!token)
		return (NULL);
	while (token[++i])
	{
		if (token[i] == '\'' || token[i] == '\"')
		{
			check_opened_quotes(ms, token, i + 1, token[i]);
			token = del_quotes(token, i, ms->lst_quote + 1, \
			token[i]);
			if (!token)
				return (NULL);
			i = ms->lst_quote - 2;
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
			i = ms->lst_quote;
		}
	}
	return (0);
}
