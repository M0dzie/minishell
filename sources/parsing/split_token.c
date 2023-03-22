/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:56:59 by thmeyer           #+#    #+#             */
/*   Updated: 2023/03/22 14:27:08 by thmeyer          ###   ########.fr       */
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
			if (input[i] == '|' && (!is_space(input[i - 1]) || !is_space(input[i + 1])))
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

char	**ms_strtok(t_msl *ms, char *input)
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
			if (in_quote && input[i] == ms->fst_delim)
				in_quote = 0;
			else if (!in_quote)
			{
				in_quote = 1;
				ms->fst_delim = input[i];
			}
		}
		if (!in_quote && (is_space(input[i]) || input[i] == '|' || \
		input[i] == '>' || input[i] == '<'))
		{
			if (k > 0)
			{
				token[++j] = get_token(ms, input, i, k);
				if (!token[j])
					return (NULL);
				k = 0;
			}
			if ((input[i] == '>' && input[i + 1] == '>') || \
			(input[i] == '<' && input[i + 1] == '<'))
			{
				token[++j] = ft_calloc(3, sizeof(char));
				if (!token[j])
					return (NULL);
				token[j][0] = input[i];
				token[j][1] = input[i + 1];
				i++;
			}
			else if (input[i] == '|' || input[i] == '<' || \
			input[i] == '>')
			{
				token[++j] = ft_calloc(2, sizeof(char));
				if (!token[j])
					return (NULL);
				token[j][0] = input[i];
			}
		}
		else
			k++;
	}
	if (k > 0)
	{
		token[++j] = get_token(ms, input, i, k);
		if (!token[j])
			return (NULL);
	}
	return (token);
}

// char	**ms_strtok(t_msl *ms, char *input)
// {
// 	char	**token;

// 	token = ft_calloc((count_tokens(input) + 1), sizeof(char *));
// 	if (!token)
// 		return (NULL);
// 	parse_tokens(ms, input, token);
// 	return (token);
// }

// void	parse_tokens(t_msl *ms, char *input, char **token)
// {
// 	int		i;
// 	int		j;
// 	int		k;
// 	int		in_quote;

// 	i = -1;
// 	j = -1;
// 	k = 0;
// 	in_quote = 0;
// 	while (input[++i])
// 	{
// 		in_quote = handle_quotes(ms, input, &in_quote, i);
// 		if (!in_quote)
// 			handle_token(ms, input, &j, &k, token, i);
// 		else
// 			k++;
// 	}
// 	if (k > 0)
// 		handle_last_token(ms, input, &j, &k, token, i);
// }

// int		handle_quotes(t_msl *ms, char *input, int *in_quote, int i)
// {
// 	if ((input[i] == '\"' || input[i] == '\'') && (i == 0 \
// 	|| ft_isascii(input[i - 1])))
// 	{
// 		if (*in_quote && input[i] == ms->fst_delim)
// 			*in_quote = 0;
// 		else if (!*in_quote)
// 		{
// 			*in_quote = 1;
// 			ms->fst_delim = input[i];
// 		}
// 	}
// 	return (*in_quote);
// }

// void	handle_token(t_msl *ms, char *input, int *j, int *k, char **token, int i)
// {
// 	if (is_token_delimiter(input[i]))
// 	{
// 		if (*k > 0)
// 		{
// 			token[++(*j)] = get_token(ms, input, i, *k);
// 			if (!token[*j])
// 				return ;
// 			*k = 0;
// 		}
// 		handle_special_token(input, j, token, i);
// 	}
// 	else
// 		(*k)++;
// }

// void	handle_special_token(char *input, int *j, char **token, int i)
// {
// 	if ((input[i] == '>' && input[i + 1] == '>') || \
// 		(input[i] == '<' && input[i + 1] == '<'))
// 	{
// 		token[++(*j)] = ft_calloc(3, sizeof(char));
// 		if (!token[*j])
// 			return ;
// 		token[*j][0] = input[i];
// 		token[*j][1] = input[i + 1];
// 		i++;
// 	}
// 	else if (input[i] == '|' || input[i] == '<' || \
// 		input[i] == '>')
// 	{
// 		token[++(*j)] = ft_calloc(2, sizeof(char));
// 		if (!token[*j])
// 			return ;
// 		token[*j][0] = input[i];
// 	}
// }

// void	handle_last_token(t_msl *ms, char *input, int *j, int *k, char **token, int i)
// {
// 	token[++(*j)] = get_token(ms, input, i, *k);
// 	if (!token[*j])
// 		return ;
// }
