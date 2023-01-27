/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 08:57:27 by thmeyer           #+#    #+#             */
/*   Updated: 2022/11/21 13:29:32 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief outputs the character ’c’ to the given file descriptor
 * @param c 
 * @param fd
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
