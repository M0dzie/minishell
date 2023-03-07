/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:35:45 by thmeyer           #+#    #+#             */
/*   Updated: 2023/03/07 17:44:36 by thmeyer          ###   ########.fr       */
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
	split = ft_strtrim(split, "$ \'\"");
	if (!split)
		return (NULL);
	printf("clean var = %s\n", split);
	if (!split[0])
		return ("$");
	if (split[0] == '?')
		return (ft_itoa(ms->status));
	// je dois penser a garder que la variables STRICTE donc refaire un check
	// $, le seul delim qui reste -> strncmp ?
	return ("Salut");
}

char	*switch_var(t_msl *ms, char *split, int i)
{
	int		j;
	char	*var;
	char	*before;
	char	*next;

// je peux mix des check malloc
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
