/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:19:36 by thmeyer           #+#    #+#             */
/*   Updated: 2022/11/22 13:59:00 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief Applies the function 'f' to each character of the string 's', and 
 * passing its index as first argument to create a new string with malloc
 * @param s the string on which to iterate
 * @param f the function to apply to each character
 * @return The string created from the successive applications of 'f' or returns 
 * NULL if the allocation fails
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*strmapi;

	i = 0;
	if (!s || !f)
		return (NULL);
	strmapi = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!strmapi)
		return (NULL);
	while (s[i])
	{
		strmapi[i] = f(i, s[i]);
		i++;
	}
	strmapi[i] = '\0';
	return (strmapi);
}
