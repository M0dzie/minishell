/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 11:16:57 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/16 10:52:34 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	display_errors(t_msl *ms, int type)
{
	ft_putstr_fd("minishell: ", 2);
	if (type == 0)
		ft_putendl_fd("command not found", 2);
	if (type == '"')
		ft_putendl_fd("double quotes must be closed", 2);
	if (type == 39)
		ft_putendl_fd("single quotes must be closed", 2);
	if (type == ';' || type == '\\')
	{
		ft_putstr_fd("syntax error near unexpected token '", 2);
		ft_putstr_fd(ms->input, 2);
		ft_putendl_fd("'", 2);
	}
	if (type == '/')
	{
		ft_putstr_fd(ms->input, 2);
		ft_putendl_fd(": Is a directory", 2);
	}
}
 
int	parsing_errors(t_msl *ms)
{
	if (ms->input[0] == ';' || ms->input[0] == '\\' || ms->input[0] == '/')
		return (display_errors(ms, ms->input[0]), 0);
	if (ms->input[0] == '!' || ms->input[0] == ':' || ms->input[0] == '\t')
		return (0);
	return (0);
}
