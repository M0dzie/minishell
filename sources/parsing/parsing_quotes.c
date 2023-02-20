/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:49:43 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/20 17:20:44 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_opened_quotes(t_msl *ms, int i, char c)
{
	printf("open quote = %s\n", ms->input + i);
	if (ms->input[i] == '\0')
		return (1);
	while (ms->input[i] && ms->input[i] != c)
		i++;
	if (ms->input[i] == c)
		return (ms->lst_quote = i, 0);
	return (1);
}

char	*get_old_line(char *input, int index)
{
	int		i;
	char	*old_line;

	i = -1;
	old_line = malloc(sizeof(char) * index + 1);
	if (!old_line)
		return (NULL);
	while (++i < index)
		old_line[i] = input[i];
	old_line[i] = '\0';
	return (old_line);
}

char	*del_quotes(char *input, int index, char c)
{
	int		i;
	char	*old_line;
	char	*new_line;
	char	**split;

	i = -1;
	old_line = get_old_line(input, index);
	new_line = ft_calloc(1, 1);
	split = ft_split(input + index, c);
	if (!new_line || !old_line || !split)
		return (NULL);
	while (split[++i])
	{
		new_line = ft_strjoin(new_line, split[i]);
		if (!new_line)
			return (NULL);
	}
	ft_arrfree(split);
	new_line = ft_strjoin(old_line, new_line);
	if (!new_line)
		return (NULL);
	return (free(old_line), new_line);
}

int	parsing_quotes(t_msl *ms)
{
	int		i;
	char	*input;

	i = -1;
	input = ms->input;
	while (input[++i])
	{
		printf("input[%d] = %s\n", i, input + i);
		if (input[i] == 34 || input[i] == 39)
		{
			if (check_opened_quotes(ms, i + 1, input[i]))
				return (display_errors(ms, input[i]));
			input = del_quotes(input, i, input[i]);
			i = ms->lst_quote - 2;
		}
	}
	ms->input = input;
	if (ms->input[0] == '\0' || ms->input[0] == ' ')
		return (display_errors_pipe(ms, ms->input[0]));
	return (0);
}

// int	check_opened_quotes(t_msl *ms, int i, char c)
// {
// 	printf("open quote = %s\n", ms->input + i);
// 	if (ms->input[i] == '\0')
// 		return (1);
// 	while (ms->input[i] && ms->input[i] != c)
// 		i++;
// 	if (ms->input[i] == c)
// 		return (ms->lst_quote = i, 0);
// 	return (1);
// }

// int	word_len_in_quotes(t_msl *ms, int i)
// {
// 	int	len;

// 	len = 0;
// 	while (i + len < ms->lst_quote)
// 		len++;
// 	return (len);
// }

// char	*del_quotes(t_msl *ms, int i, char quote)
// {
// 	int		j;
// 	int		len;
// 	char	*new;

// 	j = -1;
// 	len = word_len_in_quotes(ms, i) + 1;
// 	printf("len = %d\n", len);
// 	new = ft_calloc(len + 1, sizeof(char));
// 	// new = malloc(sizeof(char) * len + 1);
// 	if (!new)
// 		return (NULL);
// 	printf("input = %s\n", ms->input + i);
// 	ft_strlcpy(new, ms->input + i, len + 1);
// 	printf("new1 = %s\n", new);
// 	new = ft_strtrim(new, &quote);
// 	if (!new)
// 		return (NULL);
// 	// if (ms->first)
// 	// 	new = ft_strjoin(new, ms->input + ms->lst_quote + 1);
// 	// else
// 	// 	new = ft_strjoin(ms->input, new);
// 	// if (!new)
// 	// 	return (NULL);
// 	printf("new2 = %s\n", new);
// 	return (new);
// }

// int	parsing_quotes(t_msl *ms)
// {
// 	int		i;
// 	// char	*input;

// 	i = -1;
// 	// input = ms->input;
// 	while (ms->input[++i])
// 	{
// 		if (ms->input[i] == 34 || ms->input[i] == 39)
// 		{
// 			if (check_opened_quotes(ms, i + 1, ms->input[i]))
// 				return (display_errors(ms, ms->input[i]));
// 			printf("len_word = %d\n", word_len_in_quotes(ms, i - 1));
// 			del_quotes(ms, i, ms->input[i]);
// 			i = ms->lst_quote;
// 		}
// 	}
// 	if (ms->input[0] == '\0' || ms->input[0] == ' ')
// 		return (display_errors_pipe(ms, ms->input[0]));
// 	return (0);
// }
