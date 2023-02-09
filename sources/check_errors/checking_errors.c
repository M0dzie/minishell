/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:57 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/09 14:03:17 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	checking_quotes(char *input, char c, int *status)
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
		return (*status = 0, ft_putendl_fd("Quotes must be closed.", 2));
}

int	parsing_errors(char *input)
{
	int	i;
	int	status;

	status = 1;
	i = -1;
	while (input[++i])
	{
		if ((input[i] == 34 || input[i] == 39) && status == 1)
			return (checking_quotes(input, input[i], &status), -1);
		else if (input[i] == ';')
			return (ft_putendl_fd("Syntax error near unexpected token `;`"\
			, 2), -1);
		else if (input[i] == '\\')
			return (ft_putendl_fd("Syntax error near unexpected token `\\`"\
			, 2), -1);
	}
}
