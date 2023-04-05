/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 01:25:02 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/04/05 01:26:18 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	elem_addback(t_elem **stack, t_elem *new_elem)
{
	t_elem	*addback;

	if (!(*stack))
		(*stack) = new_elem;
	else
	{
		addback = (*stack);
		while (addback->next != NULL)
			addback = addback->next;
		addback->next = new_elem;
	}
}

t_elem	*new_elem(char *name, int type)
{
	t_elem	*new_elem;

	new_elem = malloc(sizeof(t_elem));
	if (!new_elem)
		return (display_error_exec("minishell: ", "new_elem", 15), NULL);
	new_elem->name = ft_strdup_null(name);
	new_elem->type = type;
	new_elem->next = NULL;
	return (new_elem);
}
