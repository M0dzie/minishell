/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:52:15 by msapin            #+#    #+#             */
/*   Updated: 2023/04/04 17:52:34 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtins(char *cmd)
{
	if (!cmd || !cmd[0])
		return (0);
	if (match_multi("/usr/bin/echo", "/bin/echo", "echo", cmd) |
		match_multi("/usr/bin/pwd", "/bin/pwd", "pwd", cmd) |
		match_multi("/usr/bin/env", "/bin/env", "env", cmd) |
		ft_strmatch("cd", cmd) | ft_strmatch("unset", cmd) |
		ft_strmatch("export", cmd) | ft_strmatch("exit", cmd))
		return (1);
	return (0);
}
