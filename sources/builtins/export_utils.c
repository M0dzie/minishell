/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:44:16 by msapin            #+#    #+#             */
/*   Updated: 2023/04/04 14:47:42 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	invalid_first(char *name)
{
	char	*invalid_char;
	int		i;

	if (!name[0])
		return (1);
	invalid_char = "1234567890=";
	i = -1;
	while (invalid_char[++i])
	{
		if (invalid_char[i] == name[0])
			return (1);
	}
	return (0);
}

static int	invalid_option(char *name)
{
	char	*invalid_opt;
	int		i;
	int		namelen;

	namelen = ft_strlen(name);
	if (name[0] == '-' && namelen > 1)
	{
		invalid_opt = ft_calloc(3, sizeof(char));
		if (!invalid_opt)
			return (display_error_exec("minishell: ", "getenv_var: ", 6), 1);
		invalid_opt[0] = name[0];
		invalid_opt[1] = name[1];
		return (display_error_exec("minishell: export: ", invalid_opt, 1), 1);
	}
	return (0);
}

int	invalid_identifier(char *name)
{
	char	*invalid_char;
	int		i;
	int		j;

	if (invalid_first(name))
		return (display_error_exec("minishell: export: '", name, 14), 1);
	else if (invalid_option(name))
		return (2);
	invalid_char = "`~!@#$%^&*-+.,\\?:{}[]";
	i = 0;
	while (name[i] && name[i] != '=')
	{
		j = -1;
		while (invalid_char[++j])
		{
			if (name[i] == invalid_char[j])
				return (display_error_exec("minishell: export: '", name, 14),
					1);
		}
		i++;
	}
	return (0);
}
