/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:36:08 by thmeyer           #+#    #+#             */
/*   Updated: 2023/01/23 13:39:56 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_tab(char **all_arg)
{
	int	i;

	i = -1;
	while (all_arg[++i])
		free(all_arg[i]);
	free(all_arg);
}

void	free_stack(t_list **lst)
{
	t_list	*next_lst;

	while ((*lst))
	{
		next_lst = (*lst)->next;
		free((*lst));
		(*lst) = next_lst;
	}
	(*lst) = NULL;
}
