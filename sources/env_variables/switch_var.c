/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:35:45 by thmeyer           #+#    #+#             */
/*   Updated: 2023/03/15 13:32:17 by thmeyer          ###   ########.fr       */
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

	printf("get_value = %s\n", token);
	if (token[0] == '?')
		return (ft_itoa(ms->status));
	if (token[0] == '\"' || token[0] == '\'')
		return ("");
	if (ft_isdigit(token[0]))
		return ("");
	if (token[0] == '$' || token[0] == ' ' || !token[0] | !ft_isalpha(token[0]))
		return (ms->f_quote++, "$");
	i = 0;
	while (token[i] && token[i] != '\"' && token[i] != '\'' && \
	token[i] != ' ' && token[i] != '$')
		i++;
	token = get_before_delim(token, i);
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

	while (token[i] && token[i] != '$')
		i++;
	ms->f_quote = i - 1;
	before = get_before_delim(token, i);
	var = get_value(ms, token + ++i);
	if (!before || !var)
		return (free(before), NULL);
	while (token[i] && (ft_isalpha(token[i]) || token[i] == '?') && token[i] != '\"' \
	&& token[i] != '\'' && token[i] != ' ' && token[i] != '$')
		i++;
	next = get_after_delim(token, i);
	if (!next)
		return (free(before), free(var), NULL);
	var = clear_line(before, var, next);
	if (!var)
		return (free(before), free(next), NULL);
	return (free(before), free(next), free(token), var);
}
