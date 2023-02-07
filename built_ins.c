/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:55:12 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/07 10:59:06 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pwd(void)
{
	printf("%s\n", getenv("PWD"));
}

void	print_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n",env[i]);
}