/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:54:52 by msapin            #+#    #+#             */
/*   Updated: 2023/04/04 14:56:52 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	invalid_option_unset(char *name)
{
	char	*invalid_opt;
	int		i;
	int		namelen;

	namelen = ft_strlen(name);
	if (name[0] == '-' && namelen > 1)
	{
		invalid_opt = ft_calloc(3, sizeof(char));
		if (!invalid_opt)
			return (display_error_exec("minishell: ", "invalid_opt: ", 6), 1);
		invalid_opt[0] = name[0];
		invalid_opt[1] = name[1];
		return (display_error_exec("minishell: unset: ", invalid_opt, 1), 1);
	}
	return (0);
}

int	invalid_identifier_unset(char *name)
{
	char	*invalid_char;
	int		i;
	int		j;

	if (!name[0])
		return (display_error_exec("minishell: unset: '", name, 14), 1);
	if (invalid_option_unset(name))
		return (2);
	if (ft_isdigit(name[0]))
		return (display_error_exec("minishell: unset: '", name, 14), 1);
	invalid_char = "!?@#$%^`~&*/\\{}[]-=+;:'\".,<>|";
	i = -1;
	while (name[++i])
	{
		j = -1;
		while (invalid_char[++j])
		{
			if (name[i] == invalid_char[j])
				return (display_error_exec("minishell: unset: '", name, 14), 1);
		}
	}
	return (0);
}

void	update_arr(t_msl *ms)
{
	if (ms->arrenv)
		ft_arrfree(ms->arrenv);
	if (ms->arrexport)
		ft_arrfree(ms->arrexport);
	ms->arrenv = ft_getenv(ms);
	ms->arrexport = ft_getexport(ms);
}
