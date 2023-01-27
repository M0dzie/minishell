/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:01:21 by thmeyer           #+#    #+#             */
/*   Updated: 2022/11/21 13:22:24 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief allocates with malloc enough space for count objects that are size 
 * bytes of memory each
 * @param count 
 * @param size 
 * @return a pointer to allocated memory
 */
void	*ft_calloc(size_t count, size_t size)
{
	char	*str;

	if (size > 0 && count > SIZE_MAX / size)
		return (NULL);
	str = malloc(size * count);
	if (!str)
		return (NULL);
	ft_bzero(str, count * size);
	return (str);
}
