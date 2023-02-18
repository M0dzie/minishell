/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:57 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/18 21:45:44 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	display_errors(t_msl *ms, int type)
{
	ft_putstr_fd("minishell: ", 2);
	if (type == 34)
		ft_putendl_fd("double quotes must be closed", 2);
	if (type == 39)
		ft_putendl_fd("single quotes must be closed", 2);
	if (type == '|' && (ms->input[1] == ' ' || ms->input[1] == '\0' \
	|| ft_isalpha(ms->input[1])))
		ft_putendl_fd("syntax error near unexpected token '|'", 2);
	if (type == '|' && ms->input[1] == '|')
		ft_putendl_fd("syntax error near unexpected token '||'", 2);
	if (type == '&' && (ms->input[1] == ' ' || ms->input[1] == '\0'))
		ft_putendl_fd("syntax error near unexpected token '&'", 2);
	if (type == '&' && ms->input[1] == '&')
		ft_putendl_fd("syntax error near unexpected token '&&'", 2);
	if (type == ';' && (ms->input[1] == ' ' || ms->input[1] == '\0'))
		ft_putendl_fd("syntax error near unexpected token ';'", 2);
	if (type == ';' && ms->input[1] == ';')
		ft_putendl_fd("syntax error near unexpected token ';;'", 2);
	if (type == '(' && (ms->input[1] == ' ' || ms->input[1] == '\0' \
	|| ms->input[1] == ')' || ms->input[1] == '('))
		ft_putendl_fd("syntax error near unexpected token ')'", 2);
	return (-1);
}

int	display_errors_pipe(t_msl *ms, int type)
{
	int	i;

	i = -1;
	ft_putstr_fd("minishell: ", 2);
	if (type == ' ' || type == 0)
	{
		while (ms->input[++i] && ms->input[i] != '|')
			ft_putchar_fd(ms->input[i], 2);
		ft_putendl_fd(": command not found", 2);
		if (ms->input[i] == '|')
			return (ms->input = ft_strtrim(&ms->input[i + 1], " "), 0);
	}
	if (type == '/')
	{
		while (ms->input[++i] && ms->input[i] != '|')
			ft_putchar_fd(ms->input[i], 2);
		ft_putendl_fd(": Is a directory", 2);
		if (ms->input[i] == '|')
			return (ms->input += i + 1, 0);
	}
	return (-1);
}

int	parsing_errors(t_msl *ms)
{
	if (ms->input[0] == '/' || ms->input[0] == ' ')
		return (display_errors_pipe(ms, ms->input[0]));
	if (ms->input[0] == '|' || ms->input[0] == '&' || ms->input[0] == ';' \
	|| ms->input[0] == '(')
		return (display_errors(ms, ms->input[0]));
	if (ms->input[0] == '>' || ms->input[0] == '<')
		return (display_errors_redirect(ms, ms->input[0]));
	if (ms->input[0] == '!' || ms->input[0] == ':' || ms->input[0] == '\t' \
	|| ms->input[0] == '#')
		return (-1);
	return (0);
}
