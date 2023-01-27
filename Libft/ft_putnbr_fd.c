/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 09:08:17 by thmeyer           #+#    #+#             */
/*   Updated: 2022/11/23 16:59:21 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief outputs the integer ’n’ to the given file descriptor
 * @param n 
 * @param fd 
 */
void	ft_putnbr_base(int n, int fd)
{
	long int	lng_n;

	lng_n = (long int)n;
	if (lng_n < 0)
	{
		lng_n *= -1;
		ft_putchar_fd('-', fd);
	}	
	if (lng_n >= 0 && lng_n < 10)
		ft_putchar_fd((lng_n + '0'), fd);
	else
	{
		ft_putnbr_base((lng_n / 10), fd);
		ft_putnbr_base((lng_n % 10), fd);
	}
}
