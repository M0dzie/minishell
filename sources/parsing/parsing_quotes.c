/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:49:43 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/20 19:17:50 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_opened_quotes(t_msl *ms, int i, char c)
{
	if (ms->input[i] == '\0')
		return (1);
	while (ms->input[i] && ms->input[i] != c)
		i++;
	if (ms->input[i] == c)
		return (ms->lst_quote = i, 0);
	return (1);
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

char	*clear_line(char *input, char *before_quote, char *line, char *after_quote)
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

char	*del_quotes(char *input, int index, int lst_quote, char quote)
{
	int		i;
	char	*before_quote;
	char	*new_line;
	char	*after_quote;
	char	**split;

	i = -1;
	before_quote = get_before_quote(input, index);
	after_quote = get_after_quote(input, lst_quote);
	new_line = ft_calloc(1, 1);
	split = ft_split(input + index, quote);
	if (!new_line || !before_quote || !split || !after_quote)
		return (NULL);
	while (split[++i])
	{
		new_line = ft_strjoin(new_line, split[i]);
		if (!new_line)
			return (NULL);
	}
	ft_arrfree(split);
	new_line = clear_line(input, before_quote, new_line, after_quote);
	if (!new_line)
		return (NULL);
	printf("new_line = %s\n", new_line);
	return (free(before_quote), free(after_quote), new_line);
}

// char	*del_quotes(char *input, int index, char c)
// {
// 	int		i;
// 	char	*old_line;
// 	char	*new_line;
// 	char	**split;

// 	i = -1;
// 	old_line = get_before_quote(input, index);
// 	new_line = ft_calloc(1, 1);
// 	split = ft_split(input + index, c);
// 	if (!new_line || !old_line || !split)
// 		return (NULL);
// 	while (split[++i])
// 	{
// 		new_line = ft_strjoin(new_line, split[i]);
// 		if (!new_line)
// 			return (NULL);
// 	}
// 	ft_arrfree(split);
// 	new_line = ft_strjoin(old_line, new_line);
// 	if (!new_line)
// 		return (NULL);
// 	return (free(old_line), new_line);
// }

int	parsing_quotes(t_msl *ms)
{
	int		i;

	i = -1;
	while (ms->input[++i])
	{
		if (ms->input[i] == 34 || ms->input[i] == 39)
		{
			if (check_opened_quotes(ms, i + 1, ms->input[i]))
				return (display_errors(ms, ms->input[i]));
			ms->input = del_quotes(ms->input, i, ms->lst_quote + 1, ms->input[i]);
			i = ms->lst_quote - 2;
		}
		// if (ms->input[ms->lst_quote - 1] == '\0')
		// 	break ;
	}
	if (ms->input[0] == '\0' || ms->input[0] == ' ')
		return (display_errors_pipe(ms, ms->input[0]));
	return (0);
}
