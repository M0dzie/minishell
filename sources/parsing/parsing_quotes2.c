/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 11:13:09 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/21 11:15:10 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	printf("before_quote = %s\n", before_quote);
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
	printf("after_quote = %s\n", after_quote);
	return (after_quote);
}

char	*clear_line(char *input, char *before_quote, char *line, \
char *after_quote)
{
	int		i;
	int		j;
	int		w_len;
	char	*clear;

	i = -1;
	j = -1;
	clear = ft_calloc(ft_strlen(before_quote) + ft_strlen(after_quote) + 1, \
	sizeof(char));
	if (!clear)
		return (NULL);
	while (before_quote[++i])
		clear[i] = before_quote[i];
	printf("b_clear = %s\n", clear);
	while (++j < (ft_strlen(input) - ft_strlen(after_quote) - 2))
		clear[i++] = line[j];
	j = -1;
	printf("l_clear = %s\n", clear);
	while (after_quote[++j])
		clear[i++] = after_quote[j];
	printf("a_clear = %s\n", clear);
	return (free(line), clear);
}
