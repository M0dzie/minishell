/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:41:17 by thmeyer           #+#    #+#             */
/*   Updated: 2022/12/29 14:44:58 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief returns the last node of the list
 * @param lst the beginning of the list
 * @return the last node of the list
 */
t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last_lst;

	if (!lst)
		return (0);
	while (lst)
	{
		last_lst = lst;
		lst = lst->next;
	}
	return (last_lst);
}
