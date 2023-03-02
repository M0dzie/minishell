/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:13:09 by thmeyer           #+#    #+#             */
/*   Updated: 2023/03/02 18:16:33 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*word_to_change(char *input, char quote)
{
	int		len;
	char	*word;

	len = 0;
	while (input[len] != quote)
		len++;
	word = ft_calloc(len + 1, sizeof(char));
	if (!word)
		return (NULL);
	while (len--)
		word[len] = input[len];
	return (word);
}

char	*get_before_quote(char *input, int index)
{
	int		i;
	char	*before_quote;

	i = -1;
	before_quote = malloc(sizeof(char) * index + 1);
	if (!before_quote)
		return (NULL);
	while (++i < index)
		before_quote[i] = input[i];
	before_quote[i] = '\0';
	return (before_quote);
}

char	*get_after_quote(char *input, int index)
{
	int		i;
	int		len;
	char	*after_quote;

	i = -1;
	len = ft_strlen(input) - index;
	after_quote = ft_calloc(len + 1, sizeof(char));
	if (!after_quote)
		return (NULL);
	while (i++ < len)
		after_quote[i] = input[index + i];
	return (after_quote);
}

char	*clear_line(char *before_quote, char *new_word, char *after_quote)
{
	int		i;
	int		j;
	int		w_len;
	char	*clear;

	i = -1;
	j = -1;
	clear = ft_calloc(ft_strlen(before_quote) + ft_strlen(after_quote) + \
	ft_strlen(new_word) + 1, sizeof(char));
	if (!clear)
		return (NULL);
	while (before_quote[++i])
		clear[i] = before_quote[i];
	while (++j < ft_strlen(new_word))
		clear[i++] = new_word[j];
	j = -1;
	while (after_quote[++j])
		clear[i++] = after_quote[j];
	return (clear);
}

char	*del_quotes(char *input, int index, int lst_quote, char quote)
{
	char	*new_word;
	char	*before_quote;
	char	*after_quote;
	char	*new_line;

	before_quote = get_before_quote(input, index);
	new_word = word_to_change(input + index + 1, quote);
	after_quote = get_after_quote(input, lst_quote);
	if (!before_quote || !new_word || !after_quote)
		return (NULL);
	new_line = clear_line(before_quote, new_word, after_quote);
	if (!new_line)
		return (NULL);
	return (free(before_quote), free(new_word), free(after_quote), \
	free(input), new_line);
}
