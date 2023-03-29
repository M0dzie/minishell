/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:56:59 by thmeyer           #+#    #+#             */
/*   Updated: 2023/03/29 14:52:44 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_token(t_msl *ms, char *input, int i, int k)
{
	char	*token;

	token = ft_calloc((k + 1), sizeof(char));
	if (!token)
		return (NULL);
	ft_strlcpy(token, input + (i - k), k + 1);
	token = parsing_quotes_split(ms, token);
	if (!token)
		return (NULL);
	return (token);
}

static int	handle_special_token(t_msl *ms, char *input, int *j, int *k)
{
	ms->fst_delim = 0;
	if ((input[0] == '>' && input[1] == '>') || \
		(input[0] == '<' && input[1] == '<'))
	{
		ms->tokens[++(*j)] = ft_calloc(3, sizeof(char));
		if (!ms->tokens[*j])
			return (0);
		ms->tokens[*j][0] = input[0];
		ms->tokens[*j][1] = input[1];
		ms->fst_delim = 1;
		return (1);
	}
	if (input[0] == '|' || input[0] == '<' || input[0] == '>')
	{
		ms->tokens[++(*j)] = ft_calloc(2, sizeof(char));
		if (!ms->tokens[*j])
			return (0);
		ms->tokens[*j][0] = input[0];
		return (1);
	}
	return (0);
}

static int	handle_token(t_msl *ms, char *input, int *j, int *k)
{
	int		ret;
	char	*tmp;

	ret = 0;
	if (*k > 0)
	{
		tmp = get_token(ms, input, 0, (*k));
		if (tmp)
		{
			ms->tokens[++(*j)] = tmp;
			ret = 1;
		}
		*k = 0;
	}
	if (handle_special_token(ms, input, j, k))
	{
		ret = 1;
		if (!ms->tokens[*j])
			return (ret);
	}
	return (ret);
}

static void	parse_input(t_msl *ms, char *input, int j, int k)
{
	int	i;
	int	in_quote;

	i = -1;
	in_quote = 0;
	while (input[++i])
	{
		in_quote = is_in_quote(ms, input + i, in_quote);
		if (!in_quote && is_token_delimiter(input[i]))
		{
			if (handle_token(ms, input + i, &j, &k))
				if (!ms->tokens[j])
					return ;
			i += ms->fst_delim;
		}
		else
			k++;
	}
	if (handle_token(ms, input + i, &j, &k))
		if (!ms->tokens[j])
			return ;
}

void	ms_strtok(t_msl *ms, char *input)
{
	int		j;
	int		k;

	ms->tokens = ft_calloc((count_tokens(input) + 1), sizeof(char *));
	if (!ms->tokens)
		return (free(input));
	j = -1;
	k = 0;
	parse_input(ms, input, j, k);
	if (!ms->tokens)
		return (free(input), ft_arrfree(ms->tokens));
	free(input);
}
