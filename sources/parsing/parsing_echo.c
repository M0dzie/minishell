/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 21:55:22 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/23 12:24:25 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//ne pas oublier d'envoyer tous les espaces donc ne pas split ' '

int	find_echo(t_msl *ms, char *input)
{
	int		i;

	i = -1;
	printf("find_echo\n");
	while (input[++i])
	{
		if (check_opened_quotes(ms, i + 1, input[i]))
			return (display_errors(input, input[i]));
		if (ft_strncmp(input + i, "echo", 4) == 0)
			return (1);
	}
	return (0);
}

void	parsing_echo(t_msl *ms)
{
	printf("input_echo = %s\n", ms->input);
}
