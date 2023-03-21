/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:35:45 by thmeyer           #+#    #+#             */
/*   Updated: 2023/03/21 17:02:09 by thmeyer          ###   ########.fr       */
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

	if (token[0] == '?' )
		return (ms->lst_delim = 1, ft_itoa(ms->status));
	if (token[0] == ' ' || !token[0] || token[0] == '\'' || \
	token[0] == '\"')
		return (ms->fst_delim++, ms->lst_delim = 0, "$");
	if (ft_isdigit(token[0]) || !ft_isalnum(token[0]))
		return (ms->lst_delim = 1, "");
	i = 0;
	while (token[i] && ft_isalnum(token[i]))
		i++;
	token = get_before_delim(token, i);
	if (!token)
		return (NULL);
	tmp = getvar(ms, token);
	if (!tmp)
		return (ms->lst_delim = ft_strlen(token), "");
	return (ms->lst_delim = ft_strlen(token), tmp->value);
}

char	*switch_var(t_msl *ms, char *token, int i)
{
	char	*var;
	char	*before;
	char	*next;

	while (token[i] && token[i] != '$')
		i++;
	ms->fst_delim = i - 1;
	before = get_before_delim(token, i);
	var = get_value(ms, token + ++i);
	if (!before || !var)
		return (free(before), free(token), NULL);
	i += ms->lst_delim;
	next = get_after_delim(token, i);
	if (!next)
		return (free(before), free(var), free(token), NULL);
	var = clear_line(before, var, next);
	if (!var)
		return (free(before), free(next), NULL);
	return (free(before), free(next), free(token), var);
}
