/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_quotes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 10:49:43 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/21 11:15:59 by thmeyer          ###   ########.fr       */
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
			ms->input = del_quotes(ms->input, i, ms->lst_quote + 1, \
			ms->input[i]);
			i = ms->lst_quote - 2;
		}
		// if (ms->input[ms->lst_quote - 1] == '\0')
		// 	break ;
	}
	if (ms->input[0] == '\0' || ms->input[0] == ' ')
		return (display_errors_pipe(ms, ms->input[0]));
	return (0);
}
