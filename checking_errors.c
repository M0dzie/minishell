/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:57 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/08 15:49:55 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	checking_quotes(char *input)
{
	int	i;
	int	j;

	i = -1;
	while (input[++i])
	{
		j = i;
		if (input[i] == 39)
		{
			while (input[++j])
			{
				if (input[j] == 39)
					return (0);
			}
		}
		if (input[i] == 34)
		{
			while (input[++j])
			{
				if (input[j] == 34)
					return (0);
			}
		}
	}
	return (-1);
}


void	checking_errors(char *input)
{
	if (checking_quotes(input) == -1)
		return (ft_putendl_fd("Error\nQuotes must be closed.", 2));
}
