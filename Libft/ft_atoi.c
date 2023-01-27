/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:20:36 by thmeyer           #+#    #+#             */
/*   Updated: 2023/01/05 10:26:59 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief converts the initial portion of the string pointed by str to int
 * @param str 
 * @return
 */
int	ft_atoi(const char *str)
{
	long long int	i;
	int				sign;
	long long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		if (result != ((result * 10 + (((str[i] - 48)) * sign)) / 10))
			return (((sign + 1) / 2) / -1);
		result = result * 10 + ((str[i] - 48) * sign);
		i++;
	}
	return ((int)result);
}
