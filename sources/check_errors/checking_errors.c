/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:57 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/09 12:14:13 by thmeyer          ###   ########.fr       */
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
		return (*status = 0, ft_putendl_fd("Error\nQuotes must be closed.", 2));
}

void	parsing_errors(char *input)
{
	int	i;
	int	status;

	status = 1;
	i = -1;
	while (input[++i])
	{
		if ((input[i] == 34 || input[i] == 39) && status == 1)
			checking_quotes(input, input[i], &status);
	}
}
