/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 21:55:22 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/22 18:31:34 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//ne pas oublier d'envoyer tous les espaces donc ne pas split ' '

void	parsing_echo(t_msl *ms)
{
	printf("input_echo = %s\n", ms->input);
}