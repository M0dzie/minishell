/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:35:45 by thmeyer           #+#    #+#             */
/*   Updated: 2023/03/08 15:14:37 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_sign(char *token, int i)
{
	while (token[i] && token[i] != '\"')
	{
		if (token[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*get_value(t_msl *ms, char *token)
{
	int		i;
	t_var	*tmp;

	if (token[0] == '?')
		return (ft_itoa(ms->status));
	if (token[0] == '$' || token[0] == ' ' || !token[0] || token[0] == '\'' \
	|| token[0] == '\"')
		return ("$");
	i = 0;
	while (token[i] && token[i] != '\"' && token[i] && '\'' && \
	token[i] != ' ' && token[i] != '$')
		i++;
	token = get_before_quote(token, i);
	if (!token)
		return (NULL);
	tmp = getvar(ms, token);
	if (!tmp)
		return (free(tmp), free(token), "");
	return (free(token), tmp->value);
}

char	*switch_var(t_msl *ms, char *token, int i)
{
	char	*var;
	char	*before;
	char	*next;

	while (token[i] != '$')
		i++;
	before = get_before_quote(token, i);
	var = get_value(ms, token + ++i);
	if (!before || !var)
		return (free(before), NULL);
	while (token[i] && token[i] != '\"' && token[i] != '\'' && token[i] != ' ' \
	&& token[i] != '$')
		i++;
	next = get_after_quote(token, i);
	if (!next)
		return (free(before), free(var), NULL);
	var = clear_line(before, var, next);
	if (!var)
		return (free(before), free(next), NULL);
	return (free(before), free(next), free(token), var);
}
