/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:35:45 by thmeyer           #+#    #+#             */
/*   Updated: 2023/03/07 11:21:56 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_sign(char *split, int i)
{
	while (split[i] && split[i] != '\"')
	{
		if (split[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*get_value(t_msl *ms, char *split)
{
	printf("split = %s\n", split);
	return ("Salut");
}

char	*switch_var(t_msl *ms, char *split, int i)
{
	int		j;
	char	*var;
	char	*before;
	char	*next;

// je peux mis des check malloc
	j = -1;
	while (split[i] != '$')
		i++;
	before = get_before_quote(split, i);
	if (!before)
		return (NULL);
	printf("before = %s\n", before);
	var = get_value(ms, split + i + 1);
	if (!var)
		return (free(before), NULL);
	i++;
	while (split[i] && split[i] != ' ' && split[i] != '\"' && split[i] != '\'' \
	&& split[i] != '$')
		i++;
	next = get_after_quote(split, i);
	if (!next)
		return (free(before), free(var), NULL);
	printf("next = %s\n", next);
	var = clear_line(before, var, next);
	if (!var)
		return (free(before), free(next), NULL);
	printf("var = %s\n", var);
	// if (split[i] == '$')
	// 	switch_var(ms, split, i);
	return (free(before), free(next), var);
}
