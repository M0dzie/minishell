/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:57 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/22 15:34:30 by thmeyer          ###   ########.fr       */
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
	if ((type == '(' || type == ')') && (ms->input[1] == ' ' || \
	ms->input[1] == '\0' || ms->input[1] == ')' || ms->input[1] == '('))
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

// int	parsing_pipes_input(t_msl *ms)
// {
// 	int	i;

// 	i = -1;
// 	while (ms->input[++i])
// 	{
// 		if (ms->input[i] == '|' && !ms->input[i + 1])
// 			return (ft_putendl_fd("syntax error near unexpected token '|'", \
// 			2), -1);
// 	}
// 	return (0);
// }

int	pos_pipes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|' && input[i + 1])
			return (i + 1);
		i++;
	}
	return (0);
}

int	parsing_errors(t_msl *ms, char *input, int c_pipe)
{
	if (input[0] == '/' && (input[1] == '.' || \
	input[1] == '/') || input[0] == ' ')
		return (display_errors_pipe(ms, input[0]));
	if (input[0] == '|' || input[0] == '&' || input[0] == ';' \
	|| input[0] == '(' || input[0] == ')')
		return (display_errors(ms, input[0]));
	if (input[0] == '>' || input[0] == '<')
		return (display_errors_redirect(ms, input[0]));
	if (input[0] == '!' || input[0] == ':' || input[0] == '\t' \
	|| input[0] == '#')
		return (-1);
	if (c_pipe > 0)
		parsing_errors(ms, input + pos_pipes(input), c_pipe - 1);
		// return (parsing_pipes_input(ms));
	return (0);
}
