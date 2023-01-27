/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 17:08:58 by thmeyer           #+#    #+#             */
/*   Updated: 2022/11/21 13:33:39 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief allocates with malloc sufficient memory for a copy of the string 
 * s1, does the copy, and returns a pointer to it
 * @param s1 
 * @return a pointer to the copy
 */
char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	len_dup;
	char	*str_dup;

	i = 0;
	len_dup = ft_strlen(s1);
	str_dup = malloc(sizeof(char) * (len_dup + 1));
	if (!str_dup)
		return (NULL);
	while (s1[i])
	{
		str_dup[i] = ((char *)s1)[i];
		i++;
	}
	str_dup[i] = '\0';
	return (str_dup);
}
