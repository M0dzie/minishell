/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:43:51 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/03/30 21:47:26 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_global(t_msl *ms)
{
	free_env(ms);
	ft_arrfree(ms->arrenv);
	ft_arrfree(ms->arrexport);
	close(0);
	close(1);
	close(2);

	// if (ms->input)
	// 	free(ms->input);
	// if (ms->tokens)
	// 	ft_arrfree(ms->tokens);
	// free(ms);
}
