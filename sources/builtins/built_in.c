/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:55:12 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/13 14:28:25 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_pwd(void)
{
	printf("%s\n", getenv("PWD"));
}

void	print_env(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		printf("%s\n",envp[i]);
}