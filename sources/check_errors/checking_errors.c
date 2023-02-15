/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:57 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/15 10:12:19 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_opened_quotes(char *input, char c)
{
	int	i;
	int	quote;

	quote = 0;
	i = -1;
	while (input[++i])
	{
		if (input[i] == c)
			quote++;
	}
	if (quote % 2 != 0)
	{
		if (c == 34)
			ft_putendl_fd("Double quotes must be closed.", 2);
		else
			ft_putendl_fd("Single quotes must be closed.", 2);
		return (1);
	}
	return (0);
}

char	*del_quotes(char *input, char c)
{
	int		i;
	char	*new_line;
	char	**split;

	i = 0;
	new_line = ft_calloc(0, 0);
	if (!new_line)
		return (NULL);
	split = ft_split(input, c);
	if (!split)
		return (NULL);
	while (split[i])
	{
		new_line = ft_strjoin(new_line, split[i]);
		if (!new_line)
			return (NULL);
		i++;
	}
	printf("%s\n", new_line);
	return (free(split), new_line);
}

int	check_wrong_quotes_echo(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == 34 || input[i] == 39)
			return (check_opened_quotes(input, input[i]), -1);
	}
	return (0);
}

int	parsing_errors(t_msl *ms)
{
	int	i;

	i = -1;
	// if (ft_strncmp(input, "echo", 4) == 0)
	// {
	// 	if (check_wrong_quotes_echo(input) == -1)
	// 		return (-1);
	// 	return (0);
	// }
	while (ms->input[++i])
	{
		if (ms->input[i] == 34 || ms->input[i] == 39)
		{
			if (check_opened_quotes(ms->input, ms->input[i]))
				return (-1);
			else
				ms->input = del_quotes(ms->input, ms->input[i]);
		}
		if (ms->input[i] == ';')
			return (ft_putendl_fd("Syntax error near unexpected token `;`", 2), \
			-1);
		if (ms->input[i] == '\\')
			return (ft_putendl_fd("Syntax error near unexpected token `\\`", 2), \
			-1);
	}
	return (0);
}
