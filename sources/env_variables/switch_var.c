/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:35:45 by thmeyer           #+#    #+#             */
/*   Updated: 2023/04/03 14:53:24 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		return (free(token), NULL);
	tmp = getvar(ms, token);
	if (!tmp)
		return (ms->lst_delim = ft_strlen(token), free(token), "");
	return (ms->lst_delim = ft_strlen(token), free(token), tmp->value);
}

static char	*display_signal(t_msl *ms)
{
	if (g_signal > 0)
		ms->status = g_signal;
	ms->print_sig = ft_itoa(ms->status);
	if (!ms->print_sig)
		return (NULL);
	ms->lst_delim = 1;
	g_signal = 0;
	return (ms->print_sig);
}

static char	*check_value(t_msl *ms, char *token)
{
	ms->print_sig = NULL;
	if (token[0] == '=' || token[0] == ':')
		return (ms->fst_delim++, ms->lst_delim = 0, "$");
	if (token[0] == '?')
		return (display_signal(ms));
	if (token[0] == ' ' || !token[0] || token[0] == '\'' || \
	token[0] == '\"')
	{
		if ((token[0] == '\'' || token[0] == '\"') && \
		(token[1] == '\'' || token[1] == '\"'))
			return (ms->fst_delim++, ms->lst_delim = 0, "$");
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
	if (!ms->print_sig)
		return (free(before), free(next), free(token), var);
	return (free(before), free(next), free(token), free(ms->print_sig), var);
}
