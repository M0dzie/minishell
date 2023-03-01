/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:04:40 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/27 09:58:23 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	display_errors_redirect(t_msl *ms, char *input, int type)
{
	int	i;

	i = 1;
	ft_putstr_fd("minishell: ", 2);
	if (input[i] == type)
		i++;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (input[i] == '|')
		return (ft_putendl_fd("syntax error near unexpected token '|'", \
		2), ms->status = 2, -1);	
	if (type == '<' && input[1] == '<' && input[2] == '<')
		return (ft_putendl_fd("syntax error near unexpected token '<<'", 2), \
		ms->status = 2, -1);
	if (type == '>' && input[1] == '>' && input[2] == '>')
		return (ft_putendl_fd("syntax error near unexpected token '>>'", 2), \
		ms->status = 2, -1);
	if (input[1] == '\0' || (input[1] == type && \
	input[2] == '\0') || (input[0] == '<' && input[1] == '>' && \
	input[2] == '\0'))
		return (ft_putendl_fd("syntax error near unexpected token 'newline'", \
		2), ms->status = 2, -1);
	return (display_errors_redirect2(ms, input, type));
}

int	display_errors_redirect2(t_msl *ms, char *input, int type)
{
	int	i;

	i = 0;
	if (input[0] == '>' && input[1] == '<')
		return (ft_putendl_fd("syntax error near unexpected token '<'", 2), \
		ms->status = 2, -1);
	if (input[0] == '<' && input[1] == '>')
		i = 2;
	while (input[i] == ' ' || input[i] == '\t')
		i++;
	if (input[i] == '|')
		return (ft_putendl_fd("syntax error near unexpected token '|'", \
		2), ms->status = 2, -1);
	else if (ft_isalpha(input[i]))
		return (ms->status = 0, 0);
	return (display_errors_redirect3(ms, input, type));
}

int	display_errors_redirect3(t_msl *ms, char *input, int type)
{
	int	i;

	i = 0;

	if ((type == '<' && input[1] == '<') || (type == '>' && \
	input[1] == '>'))
	{
		i = 2;
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (input[i] == '<' && input[i + 1] == '<')
			return (ft_putendl_fd("syntax error near unexpected token '<<'", \
			2), ms->status = 2, -1);
		if (input[i] == '>' && input[i + 1] == '>')
			return (ft_putendl_fd("syntax error near unexpected token '>>'", \
			2), ms->status = 2, -1);
	}
	return (display_errors_redirect4(ms, input, type));
}

int	display_errors_redirect4(t_msl *ms, char *input, int type)
{
	int	i;

	i = 0;
	if ((type == '<' || type == '>') && input[1] == ' ')
	{
		i++;
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (input[i] == '<')
			return (ft_putendl_fd("syntax error near unexpected token '<'", \
			2), ms->status = 2, -1);
		if (input[i] == '>')
			return (ft_putendl_fd("syntax error near unexpected token '>'", \
			2), ms->status = 2, -1);
	}
	return (ms->status = 0, 0);
}
