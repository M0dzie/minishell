/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:56:59 by thmeyer           #+#    #+#             */
/*   Updated: 2023/03/24 15:44:19 by thmeyer          ###   ########.fr       */
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

char	*get_token(t_msl *ms, char *input, int i, int k)
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

int	is_token_delimiter(char input)
{
	if (is_space(input) || input == '|' || input == '>' || input == '<')
		return (1);
	return (0);
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

void	handle_special_token(t_msl *ms, char *input, int *j, int *k)
{
	ms->fst_delim = 0;
	if ((input[0] == '>' && input[1] == '>') || \
		(input[0] == '<' && input[1] == '<'))
	{
		ms->tokens[++(*j)] = ft_calloc(3, sizeof(char));
		if (!ms->tokens[*j])
			return ;
		ms->tokens[*j][0] = input[0];
		ms->tokens[*j][1] = input[1];
		ms->fst_delim = 1;
	}
	else if (input[0] == '|' || input[0] == '<' || \
	input[0] == '>')
	{
		ms->tokens[++(*j)] = ft_calloc(2, sizeof(char));
		if (!ms->tokens[*j])
			return ;
		ms->tokens[*j][0] = input[0];
	}
}

void	handle_token(t_msl *ms, char *input, int *j, int *k)
{
	if (*k > 0)
	{
		ms->tokens[++(*j)] = get_token(ms, input, 0, (*k));
		if (!ms->tokens[*j])
			return ;
		*k = 0;
	}
	handle_special_token(ms, input, j, k);
	if (!ms->tokens[*j])
		return ;
}

char	**ms_strtok(t_msl *ms, char *input)
{
	int		i;
	int		j;
	int		k;
	int		in_quote;

	ms->tokens = ft_calloc((count_tokens(input) + 1), sizeof(char *));
	if (!ms->tokens)
		return (NULL);
	i = -1;
	j = -1;
	k = 0;
	in_quote = 0;
	while (input[++i])
	{
		in_quote = is_in_quote(ms, input + i, in_quote);
		if (!in_quote && is_token_delimiter(input[i]))
		{
			handle_token(ms, input + i, &j, &k);
			if (!ms->tokens[j])
				return (NULL);
			i += ms->fst_delim;
		}
		else
			k++;
	}
	handle_token(ms, input + i, &j, &k);
	if (!ms->tokens[j])
		return (NULL);
}

// char	**ms_strtok(t_msl *ms, char *input)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		in_quote;
// 	char	**token;

// 	token = ft_calloc((count_tokens(input) + 1), sizeof(char *));
// 	if (!token)
// 		return (NULL);
// 	i = -1;
// 	j = -1;
// 	k = 0;
// 	in_quote = 0;
// 	while (input[++i])
// 	{
// 		if ((input[i] == '\"' || input[i] == '\'') && (i == 0 \
// 		|| ft_isascii(input[i - 1])))
// 		{
// 			if (in_quote && input[i] == ms->fst_delim)
// 				in_quote = 0;
// 			else if (!in_quote)
// 			{
// 				in_quote = 1;
// 				ms->fst_delim = input[i];
// 			}
// 		}
// 		if (!in_quote && is_token_delimiter(input[i]))
// 		{
// 			if (k > 0)
// 			{
// 				token[++j] = get_token(ms, input, i, k);
// 				if (!token[j])
// 					return (NULL);
// 				k = 0;
// 			}
// 			if ((input[i] == '>' && input[i + 1] == '>') || \
// 			(input[i] == '<' && input[i + 1] == '<'))
// 			{
// 				token[++j] = ft_calloc(3, sizeof(char));
// 				if (!token[j])
// 					return (NULL);
// 				token[j][0] = input[i];
// 				token[j][1] = input[i + 1];
// 				i++;
// 			}
// 			else if (input[i] == '|' || input[i] == '<' || \
// 			input[i] == '>')
// 			{
// 				token[++j] = ft_calloc(2, sizeof(char));
// 				if (!token[j])
// 					return (NULL);
// 				token[j][0] = input[i];
// 			}
// 		}
// 		else
// 			k++;
// 	}
// 	if (k > 0)
// 	{
// 		token[++j] = get_token(ms, input, i, k);
// 		if (!token[j])
// 			return (NULL);
// 	}
// 	return (token);
// }
