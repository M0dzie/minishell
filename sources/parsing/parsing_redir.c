/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:04:40 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/18 10:55:17 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	display_errors_redirect(t_msl *ms, int type)
{
	int	i;

	i = 1;
	ft_putstr_fd("minishell: ", 2);
	if (ms->input[i] == type)
		i++;
	while (ms->input[i] == ' ' || ms->input[i] == '\t')
		i++;
	if (ms->input[i] == '|')
		return (ft_putendl_fd("syntax error near unexpected token '|'", \
		2), -1);	
	if (type == '<' && ms->input[1] == '<' && ms->input[2] == '<')
		return (ft_putendl_fd("syntax error near unexpected token '<<'", 2), -1);
	if (type == '>' && ms->input[1] == '>' && ms->input[2] == '>')
		return (ft_putendl_fd("syntax error near unexpected token '>>'", 2), -1);
	if (ms->input[1] == '\0' || (ms->input[1] == type && \
	ms->input[2] == '\0') || (ms->input[0] == '<' && ms->input[1] == '>' && \
	ms->input[2] == '\0'))
		return (ft_putendl_fd("syntax error near unexpected token 'newline'", \
		2), -1);
	return (display_errors_redirect2(ms, type));
}

int	display_errors_redirect2(t_msl *ms, int type)
{
	int	i;

	i = 0;
	if (ms->input[0] == '<' && ms->input[1] == '>')
		i = 2;
	while (ms->input[i] == ' ' || ms->input[i] == '\t')
		i++;
	if (ms->input[i] == '|')
		return (ft_putendl_fd("syntax error near unexpected token '|'", \
		2), -1);
	if (type == '>' && ms->input[1] == ' ' && ms->input[2] == '>')
		return (ft_putendl_fd("syntax error near unexpected token '>'", 2), -1);
	if (type == '<' && ms->input[1] == ' ' && ms->input[2] == '<')
		return (ft_putendl_fd("syntax error near unexpected token '<'", 2), -1);
	if (type == '<' && ms->input[1] == '<' && ms->input[2] == ' ' && \
	ms->input[3] == '<')
		return (ft_putendl_fd("syntax error near unexpected token '<<'", 2), -1);
	if (type == '>' && ms->input[1] == '>' && ms->input[2] == ' ' && \
	ms->input[3] == '>')
		return (ft_putendl_fd("syntax error near unexpected token '>>'", 2), -1);
	return (display_errors_redirect3(ms, type));
}

int	display_errors_redirect3(t_msl *ms, int type)
{
	int	i;

	i = 0;
	if (type == '<')
	{
		i++;
		while (ms->input[i] == ' ' || ms->input[i] == '\t')
			i++;
		if (ms->input[i] == '<')
			return (ft_putendl_fd("syntax error near unexpected token '<'", 2), -1);
		if (ms->input[i] == '>')
			return (ft_putendl_fd("syntax error near unexpected token '>'", 2), -1);
	}
	if (type == '>')
	{
		i++;
		while (ms->input[i] == ' ' || ms->input[i] == '\t')
			i++;
		if (ms->input[i] == '<')
			return (ft_putendl_fd("syntax error near unexpected token '<'", 2), -1);
		if (ms->input[i] == '>')
			return (ft_putendl_fd("syntax error near unexpected token '>'", 2), -1);
	}
	return (0);
}
