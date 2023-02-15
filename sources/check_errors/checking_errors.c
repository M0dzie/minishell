/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:57 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/15 19:13:35 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_errors(t_msl *ms, int type)
{
	ft_putstr_fd("minishell: ", 2);
	if (type == 0)
		ft_putendl_fd("command not found", 2);
	if (type == '"')
		ft_putendl_fd("double quotes must be closed", 2);
	if (type == 39)
		ft_putendl_fd("single quotes must be closed", 2);
	if (type == ';' || type == '\\')
	{
		ft_putstr_fd("syntax error near unexpected token '", 2);
		ft_putstr_fd(ms->input, 2);
		ft_putendl_fd("'", 2);
	}
	if (type == '/')
	{
		ft_putstr_fd(ms->input, 2);
		ft_putendl_fd(": Is a directory", 2);
	}
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

char	*del_quotes(t_msl *ms, char c)
{
	int		i;
	char	*new_line;
	char	**split;

	i = 0;
	new_line = ft_calloc(1, 1);
	if (!new_line)
		return (NULL);
	split = ft_split(ms->input, c);
	if (!split)
		return (NULL);
	while (split[i])
	{
		new_line = ft_strjoin(new_line, split[i]);
		if (!new_line)
			return (NULL);
		i++;
	}
	free(split);
	printf("%s\n", new_line);
	if (new_line[0] == '\0')
		return (display_errors(ms, 0), new_line);
	return (new_line);
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
				return (display_errors(ms, ms->input[i]), -1);
			else
			{
				ms->input = del_quotes(ms, ms->input[i]);
				i = -1;
			}
		}
	}
	if (ms->input[0] == ';' || ms->input[0] == '\\' || ms->input[0] == '/')
		return (display_errors(ms, ms->input[0]), 0);
	if (ms->input[0] == '!' || ms->input[0] == ':' || ms->input[0] == '\t')
		return (0);
	return (0);
}
