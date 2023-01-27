/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:11:14 by thmeyer           #+#    #+#             */
/*   Updated: 2022/11/22 14:50:27 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	str_count(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i] && set[j])
	{
		if (s1[i] == set[j])
		{
			i++;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

static size_t	str_rev_count(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(s1) - 1;
	j = 0;
	while (set[j])
	{
		if (s1[i] == set[j])
		{
			i--;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

/**
 * @brief allocates with malloc and returns a copy of 's1' with the characters 
 * specified in 'set' removed from the beginning and the end of the string
 * @param s1 
 * @param set 
 * @return the trimmed string or NULL if the allocation fails
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	i_bgn;
	size_t	i_end;
	char	*trim;

	i = 0;
	if (!s1)
		return (NULL);
	i_bgn = str_count(s1, set);
	if (i_bgn == ft_strlen(s1))
		return (ft_strdup(""));
	i_end = str_rev_count(s1, set);
	trim = malloc(sizeof(char) * ((i_end - i_bgn) + 2));
	if (!trim)
		return (NULL);
	while (i < i_end - i_bgn + 1)
	{
		trim[i] = s1[i_bgn + i];
		i++;
	}
	trim[i] = '\0';
	return (trim);
}
