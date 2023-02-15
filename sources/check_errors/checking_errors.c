/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:57 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/15 11:54:07 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_errors(int type)
{
	if (type == 0)
		ft_putendl_fd("Command not found.", 2);
	if (type == '"')
		ft_putendl_fd("Double quotes must be closed.", 2);
	if (type == 39)
		ft_putendl_fd("Single quotes must be closed.", 2);
	if (type == ';')
		ft_putendl_fd("Syntax error near unexpected token ';'.", 2);
	if (type == '\\')
		ft_putendl_fd("Syntax error near unexpected token '\\'.", 2);
}

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
		return (1);
	return (0);
}

char	*del_quotes(char *input, char c)
{
	int		i;
	char	*new_line;
	char	**split;

	i = 0;
	new_line = ft_calloc(1, 1);
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
	if (new_line[0] == '\0')
		return (free(split), display_errors(0), new_line);
	return (free(split), new_line);
}

// void	parsing_errors_echo(t_msl *ms)
// {
// 	int	i;

// 	i = -1;
// 	printf("its echo\n");
// 	while (ms->input[++i])
// 	{
// 		if (ms->input[i] == 34 || ms->input[i] == 39)
// 		{
// 			if (!check_opened_quotes(ms->input, ms->input[i]))
// 				ms->input = del_quotes(ms->input, ms->input[i]);
// 		}
// 	}
// }

int	parsing_errors(t_msl *ms)
{
	int	i;

	i = -1;
	while (ms->input[++i])
	{
		if (ms->input[i] == 34 || ms->input[i] == 39)
		{
			if (check_opened_quotes(ms->input, ms->input[i]))
				return (display_errors(ms->input[i]), -1);
			else
			{
				ms->input = del_quotes(ms->input, ms->input[i]);
				i = -1;
			}
		}
		if (ms->input[i] == ';' || ms->input[i] == '\\')
			return (display_errors(ms->input[i]), -1);
	}
	return (0);
}
