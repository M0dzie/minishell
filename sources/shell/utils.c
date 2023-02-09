/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 13:53:35 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/08 21:09:37 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Booleen TRUE = 1, FALSE = 0*/
int	ms_strcmp(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (s1[i + j] == s2[j])
		{
			j++;
			if (s2[j] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}