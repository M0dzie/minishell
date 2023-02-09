/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:55:12 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/08 21:09:55 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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