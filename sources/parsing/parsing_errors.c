/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:57 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/23 10:29:20 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	display_errors(char *input, int type)
{
	ft_putstr_fd("minishell: ", 2);
	if (type == 34)
		ft_putendl_fd("double quotes must be closed", 2);
	if (type == 39)
		ft_putendl_fd("single quotes must be closed", 2);
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
	return (-1);
}

int	display_errors_pipe(t_msl *ms, char *input, int type)
{
	int	i;

	i = -1;
	ft_putstr_fd("minishell: ", 2);
	if (type == ' ' || type == 0)
	{
		while (input[++i] && input[i] != '|')
			ft_putchar_fd(input[i], 2);
		ft_putendl_fd(": command not found", 2);
		if (input[i] == '|')
			return (input = ft_strtrim(&input[i + 1], " "), \
			ms->input = ft_strtrim(&input[i + 1], " "), 0);
	}
	if (type == '/')
	{
		while (input[++i] && input[i] != '|')
			ft_putchar_fd(input[i], 2);
		ft_putendl_fd(": Is a directory", 2);
		if (input[i] == '|')
			return (input += i + 1, ms->input += i + 1, 0);
	}
	return (-1);
}

int	pos_pipes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|' && input[i + 1] == ' ' && input[i + 2])
			return (i + 2);
		else if (input[i] == '|' && input[i + 1])
			return (i + 1);
		i++;
	}
	return (0);
}

int	parsing_errors(t_msl *ms, char *input, int c_pipe)
{
	printf("input = %s\n", input);
	if (input[0] == '/' && (input[1] == '.' || \
	input[1] == '/') || input[0] == ' ')
		return (display_errors_pipe(ms, input, input[0]));
	if (input[0] == '|' || input[0] == '&' || input[0] == ';' \
	|| input[0] == '(' || input[0] == ')')
		return (display_errors(input, input[0]));
	if (input[0] == '>' || input[0] == '<')
		return (display_errors_redirect(input, input[0]));
	if (input[0] == '\t' || input[0] == '#')
		return (-1);
	if (c_pipe > 0 && input[ft_strlen(input) - 1] == '|')
		return (ft_putendl_fd("syntax error near unexpected token '|'", 2), -1);
	if (c_pipe > 0 && input[ft_strlen(input) - 1] != '|')
		return (parsing_errors(ms, input + pos_pipes(input), c_pipe - 1));
	return (0);
}
