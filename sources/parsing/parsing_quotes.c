/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:49:43 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/22 18:20:35 by thmeyer          ###   ########.fr       */
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

int	parsing_quotes(t_msl *ms)
{
	int		i;

	i = -1;
	while (ms->input[++i])
	{
		if (ms->input[i] == 34 || ms->input[i] == 39)
		{
			if (check_opened_quotes(ms, i + 1, ms->input[i]))
				return (display_errors(ms->input, ms->input[i]));
			ms->input = del_quotes(ms->input, i, ms->lst_quote + 1, \
			ms->input[i]);
			i = ms->lst_quote - 2;
		}
	}
	if (ms->input[0] == '\0' || ms->input[0] == ' ')
		return (display_errors_pipe(ms->input, ms->input[0]));
	return (0);
}
