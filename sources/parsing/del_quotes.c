/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:13:09 by thmeyer           #+#    #+#             */
/*   Updated: 2023/03/14 09:36:34 by thmeyer          ###   ########.fr       */
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

char	*get_before_delim(char *input, int index)
{
	int		i;
	char	*before;

	i = -1;
	before = malloc(sizeof(char) * index + 1);
	if (!before)
		return (NULL);
	while (++i < index)
		before[i] = input[i];
	before[i] = '\0';
	return (before);
}

char	*get_after_delim(char *input, int index)
{
	int		i;
	int		len;
	char	*after;

	i = -1;
	len = ft_strlen(input) - index;
	after = ft_calloc(len + 1, sizeof(char));
	if (!after)
		return (NULL);
	while (i++ < len)
		after[i] = input[index + i];
	return (after);
}

char	*clear_line(char *before, char *new_word, char *after)
{
	int		i;
	int		j;
	int		w_len;
	char	*clear;

	i = -1;
	j = -1;
	clear = ft_calloc(ft_strlen(before) + ft_strlen(after) + \
	ft_strlen(new_word) + 1, sizeof(char));
	if (!clear)
		return (NULL);
	while (before[++i])
		clear[i] = before[i];
	while (++j < ft_strlen(new_word))
		clear[i++] = new_word[j];
	j = -1;
	while (after[++j])
		clear[i++] = after[j];
	return (clear);
}

char	*del_quotes(char *input, int index, int lst_quote, char quote)
{
	char	*new_word;
	char	*before;
	char	*after;
	char	*new_line;

	before = get_before_delim(input, index);
	new_word = word_to_change(input + index + 1, quote);
	after = get_after_delim(input, lst_quote);
	if (!before || !new_word || !after)
		return (free(before), free(new_word), free(after), NULL);
	new_line = clear_line(before, new_word, after);
	if (!new_line)
		return (free(before), free(new_word), free(after), NULL);
	return (free(before), free(new_word), free(after), \
	free(input), new_line);
}
