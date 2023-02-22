/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimehdi.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:05:37 by msapin            #+#    #+#             */
/*   Updated: 2023/02/22 22:12:57 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMEHDI_H
# define MINIMEHDI_H

void	display_env(t_msl *ms);
char	**ft_getenv(t_msl *ms);
void	pipe_one(char **args_cmd, t_msl *ms, char **envp);

#endif