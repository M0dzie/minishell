/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 17:43:27 by thmeyer           #+#    #+#             */
/*   Updated: 2022/12/29 14:37:41 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
 * @brief adds the node ’new’ at the end of the list
 * @param lst the address of a pointer to the first link of a list
 * @param new the address of a pointer to the node to be added to the list
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_lst;

	if (!(*lst))
		(*lst) = new;
	else
	{
		last_lst = ft_lstlast((*lst));
		last_lst->next = new;
	}
}
