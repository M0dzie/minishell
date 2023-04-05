/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 23:09:04 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/04/04 23:31:07 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	display_error_exec(char *first, char *second, int num_error)
// {	
// 	char	*err[19];

// 	err[1] = ": invalid option";
// 	err[2] = ": No such file or directory";
// 	err[3] = ": environnement PATH not found";
// 	err[4] = ": environnement SHELL not found";
// 	err[5] = ": command not found";
// 	err[6] = "cannot allocate memory";
// 	err[7] = ": cannot create or modify: ";
// 	err[8] = ": environnement VARIABLES not found";
// 	err[10] = "too many arguments";
// 	err[11] = ": numeric argument required";
// 	err[12] = ": Not a directory";
// 	err[13] = "': Permission denied";
// 	err[14] = "': not a valid identifier";
// 	err[15] = ": Cannot allocate memory";
// 	err[16] = ": HOME not set";
// 	err[17] = " not set";
// 	err[18] = ": Is a directory";
// 	ft_putstr_fd(first, 2);
// 	ft_putstr_fd(second, 2);
// 	ft_putendl_fd(err[num_error], 2);
// 	return (-1);
// }
