/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 13:27:55 by thmeyer           #+#    #+#             */
/*   Updated: 2022/11/22 09:13:58 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief allocates with malloc and returns a substring from the string 's'. The 
 * substring begins at index 'start' and is of maximum size 'len'
 * @param s 
 * @param start 
 * @param len 
 * @return the substring or NULL if the allocation fails
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		size;
	char	*substr;

	size = 0;
	if (!s)
		return (NULL);
	if (start < ft_strlen(s))
		s += start;
	else
		s += ft_strlen(s);
	while (*s++ && len--)
		size++;
	s = s - size - 1;
	substr = malloc(sizeof(char) * (size + 1));
	if (!substr)
		return (NULL);
	ft_strlcpy(substr, s, size + 1);
	return (substr);
}
