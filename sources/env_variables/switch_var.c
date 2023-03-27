/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:35:45 by thmeyer           #+#    #+#             */
/*   Updated: 2023/03/27 09:37:46 by thmeyer          ###   ########.fr       */
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

static int	ms_isalnum(int c)
{
	if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
			|| (c >= 'a' && c <= 'z') || c == '_'))
		return (0);
	return (1);
}

static char	*get_value(t_msl *ms, char *token)
{
	int		i;
	t_var	*tmp;

	i = 0;
	while (token[i] && ms_isalnum(token[i]))
		i++;
	token = get_before_delim(token, i);
	if (!token)
		return (NULL);
	tmp = getvar(ms, token);
	if (!tmp)
		return (ms->lst_delim = ft_strlen(token), "");
	return (ms->lst_delim = ft_strlen(token), tmp->value);
}

static char	*check_value(t_msl *ms, char *token)
{
	if (token[0] == '=')
		return (ms->fst_delim++, ms->lst_delim = 0, "$");
	if (token[0] == '?' )
	{
		if (g_signal > 0)
			return (ms->status = g_signal, ms->fst_delim = 1, \
			g_signal = 0, ft_itoa(ms->status));
		return (ms->lst_delim = 1, ft_itoa(ms->status));
	}
	if (token[0] == ' ' || !token[0] || token[0] == '\'' || \
	token[0] == '\"')
	{
		if ((token[0] == '\'' || token[0] == '\"') && \
		!check_opened_quotes(ms, token, 1, token[0]))
			return (ms->lst_delim = 0, "");
		return (ms->fst_delim++, ms->lst_delim = 0, "$");
	}
	if (ft_isdigit(token[0]) || !ms_isalnum(token[0]))
		return (ms->lst_delim = 1, "");
	return (get_value(ms, token));
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
	var = check_value(ms, token + ++i);
	if (!before || !var)
		return (free(before), free(token), NULL);
	i += ms->lst_delim;
	next = get_after_delim(token, i);
	if (!next)
		return (free(before), free(var), free(token), NULL);
	var = clear_line(before, var, next);
	if (!var)
		return (free(before), free(next), free(token), NULL);
	if (!var[0])
		return (free(before), free(next), free(token), free(var), NULL);
	return (free(before), free(next), free(token), var);
}
