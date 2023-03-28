/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:49:43 by thmeyer           #+#    #+#             */
/*   Updated: 2023/03/28 15:45:12 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*parsing_env_var(t_msl *ms, char *token)
{
	int	i;
	int	in_dquote;

	i = -1;
	in_dquote = 0;
	while (token[++i])
	{
		if (token[i] == '\'' && !check_opened_quotes(ms, token, i + 1, '\'') \
		&& !in_dquote)
			i = ms->lst_delim;
		if (token[i] == '$' || token[i] == '\"')
		{
			if (token[i] == '\"')
				in_dquote = !in_dquote;
			if (token[i] == '$' || (in_dquote && check_sign(token, i + 1)))
			{
				token = switch_var(ms, token, i);
				if (!token)
					return (NULL);
				i = ms->fst_delim;
			}
		}
	}
	return (token);
}

// static char	*handle_env_var(t_msl *ms, char *token)
// {
// 	char	*new;

// 	token = parsing_env_var(ms, token);
// 	if (!token)
// 		return (NULL);
// 	new = ft_calloc(ft_strlen(token) + 3, sizeof(char));
// 	if (!new)
// 		return (NULL);
// 	new[0] = '\"';
// 	ft_strlcpy(new + 1, token, ft_strlen(token) + 1);
// 	new[ft_strlen(new)] = '\"';
// 	printf("new = %s\n", new);
// 	return (new);
// }

char	*parsing_quotes_split(t_msl *ms, char *token)
{
	int	i;

	i = -1;
	// token = handle_env_var(ms, token);
	token = parsing_env_var(ms, token);
	if (!token)
		return (NULL);
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
