/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 20:57:58 by thmeyer           #+#    #+#             */
/*   Updated: 2023/04/03 15:13:13 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	is_token_delimiter(char input)
{
	if (is_space(input) || input == '|' || input == '>' || input == '<')
		return (1);
	return (0);
}

int	count_tokens(char *input)
{
	int		i;
	int		n_tok;

	i = -1;
	n_tok = 1;
	while (input[++i])
	{
		if (is_space(input[i]) || input[i] == '|' || !input[i + 1])
		{
			if (input[i] == '|' && (!is_space(input[i - 1]) || \
			!is_space(input[i + 1])))
				n_tok++;
			n_tok++;
		}
		if (input[i] == '<' || input[i] == '>')
			n_tok++;
	}
	if (ft_isalnum(input[i - 1]))
		n_tok++;
	return (n_tok);
}

int	is_in_quote(t_msl *ms, char *input, int in_quote)
{
	if (input[0] == '\"' || input[0] == '\'')
	{
		if (in_quote && input[0] == ms->fst_delim)
			in_quote = 0;
		else if (!in_quote)
		{
			in_quote = 1;
			ms->fst_delim = input[0];
		}
	}
	return (in_quote);
}
