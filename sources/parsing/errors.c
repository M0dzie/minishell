/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:57 by thmeyer           #+#    #+#             */
/*   Updated: 2023/04/04 11:06:08 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	display_errors(t_msl *ms, char *input, int type)
{
	ft_putstr_fd("minishell: ", 2);
	if (type == '\"')
		return (ft_putendl_fd("double quotes must be closed", 2), \
		ms->status = 1, -1);
	if (type == '\'')
		return (ft_putendl_fd("single quotes must be closed", 2), \
		ms->status = 1, -1);
	if (type == '|' && (input[1] == ' ' || input[1] == '\0' \
	|| ft_isalpha(input[1])))
		ft_putendl_fd("syntax error near unexpected token '|'", 2);
	if (type == '|' && input[1] == '|')
		ft_putendl_fd("syntax error near unexpected token '||'", 2);
	if (type == '&' && (input[1] == ' ' || input[1] == '\0'))
		ft_putendl_fd("syntax error near unexpected token '&'", 2);
	if (type == '&' && input[1] == '&')
		ft_putendl_fd("syntax error near unexpected token '&&'", 2);
	if (type == ';' && (input[1] == ' ' || input[1] == '\0'))
		ft_putendl_fd("syntax error near unexpected token ';'", 2);
	if (type == ';' && input[1] == ';')
		ft_putendl_fd("syntax error near unexpected token ';;'", 2);
	if ((type == '(' || type == ')') && (input[1] == ' ' || \
	input[1] == '\0' || input[1] == ')' || input[1] == '('))
		ft_putendl_fd("syntax error near unexpected token ')'", 2);
	return (ms->status = 2, -1);
}

static int	pos_pipes(t_msl *ms, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '\"') && \
		!check_opened_quotes(ms, input, i + 1, input[i]))
			i = ms->lst_delim;
		if (input[i] == '|' && input[i + 1] == ' ' && input[i + 2])
			return (i + 2);
		else if (input[i] == '|' && input[i + 1])
			return (i + 1);
		i++;
	}
	return (0);
}

static int	parsing_redir(t_msl *ms, char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if ((input[i] == '\'' || input[i] == '\"') && \
		!check_opened_quotes(ms, input, i + 1, input[i]))
			i = ms->lst_delim;
		if (input[i] == '>' || input[i] == '<')
			if (display_errors_redirect(ms, input + i, input[i]) == -1)
				return (-1);
	}
	return (0);
}

int	parsing_errors(t_msl *ms, char *input, int c_pipe)
{
	if (parsing_redir(ms, input) == -1)
		return (-1);
	if (input[0] == '|' || input[0] == '&' || input[0] == ';' \
	|| input[0] == '(' || input[0] == ')')
		return (display_errors(ms, input, input[0]));
	if (input[0] == '\t' || input[0] == '#')
		return (-1);
	if (c_pipe > 0 && input[ft_strlen(input) - 1] == '|')
		return (ft_putendl_fd("syntax error near unexpected token '|'", 2), \
		ms->status = 2, -1);
	if (c_pipe > 0 && input[ft_strlen(input) - 1] != '|')
		return (parsing_errors(ms, input + pos_pipes(ms, input), c_pipe - 1));
	return (0);
}
