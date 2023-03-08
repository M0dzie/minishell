/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:56:59 by thmeyer           #+#    #+#             */
/*   Updated: 2023/03/08 10:36:17 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	count_tokens(char *input)
{
	int		i;
	int		n_tok;

	i = -1;
	n_tok = 0;
	while (input[++i])
	{
		if ((input[i] != '\'' && input[i] != '\"' && input[i] != ' ') \
		&& (input[i + 1] == '\0' || input[i + 1] == '\'' || \
		input[i + 1] == '\"' || input[i + 1] == ' '))
			n_tok++;
	}
	return (n_tok);
}

char	**ms_split(t_msl *ms, char *input)
{
	int		i;
	int		j;
	int		k;
	int		in_quote;
	char	**token;

	token = ft_calloc((count_tokens(input) + 1), sizeof(char *));
	if (!token)
		return (NULL);
	i = -1;
	j = -1;
	k = 0;
	in_quote = 0;
	while (input[++i])
	{
		if ((input[i] == '\"' || input[i] == '\'') && (i == 0 \
		|| ft_isascii(input[i - 1])))
		{
			if (in_quote && input[i] == ms->f_quote)
				in_quote = 0;
			else if (!in_quote)
			{
				in_quote = 1;
				ms->f_quote = input[i];
			}
		}
		if (!in_quote && is_space(input[i]))
		{
			if (k > 0)
			{
				token[++j] = ft_calloc((k + 1), sizeof(char));
				if (!token[j])
					return (NULL);
				ft_strlcpy(token[j], input + (i - k), k + 1);
				token[j] = parsing_quotes_split(ms, token[j]);
				if (!token[j])
					return (NULL);
				k = 0;
			}
		}
		else
			k++;
	}
	if (k > 0)
	{
		token[++j] = ft_calloc((k + 1), sizeof(char));
		if (!token[j])
			return (NULL);
		ft_strlcpy(token[j], input + (i - k), k + 1);
		token[j] = parsing_quotes_split(ms, token[j]);
		if (!token[j])
			return (NULL);
	}
	return (token);
}
