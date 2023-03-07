/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:35:45 by thmeyer           #+#    #+#             */
/*   Updated: 2023/03/07 10:56:13 by thmeyer          ###   ########.fr       */
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

char	*switch_var(t_msl *ms, char *split, int i)
{
	int		j;
	char	*var;
	char	*before;
	char	*new;
	char	*next;

	j = -1;
	while (split[i] != '$')
		i++;
	before = get_before_quote(split, i);
	if (!before)
		return (NULL);
	printf("before = %s\n", before);
	while (split[i] && split[i] != ' ' && split[i] != '\"' && split[i] != '\'' \
	&& split[i] != '$')
		i++;
	var = "salut";
	return (var);
}
