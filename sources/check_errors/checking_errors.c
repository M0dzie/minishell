/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:57 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/14 15:59:20 by thmeyer          ###   ########.fr       */
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

int	parsing_errors(char *input)
{
	int	i;

	i = -1;
	if (ft_strncmp(input, "echo", 4) == 0)
	{
		if (check_wrong_quotes_echo(input) == -1)
			return (-1);
		return (0);
	}
	while (input[++i])
	{
		if (input[i] == 34 || input[i] == 39)
		{
			if (check_opened_quotes(input, input[i]))
				return (-1);
		}
		if (input[i] == ';')
			return (ft_putendl_fd("Syntax error near unexpected token `;`", 2), \
			-1);
		if (input[i] == '\\')
			return (ft_putendl_fd("Syntax error near unexpected token `\\`", 2), \
			-1);
	}
	return (0);
}
