/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:57 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/08 18:26:35 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*checking_quotes(char *input, char c)
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
		input = readline("> ");
	return (input);
}
