/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:57:28 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/28 16:30:13 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	read_prompt(t_msl *ms, char **envp)
{
	int	i;

	i = -1;
	ms->input = ft_strtrim(ms->input, " ");
	if (!ms->input)
		return ;
	printf("input = %s\n", ms->input);
	while (ms->input[++i])
	{
		
	}
}