/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimehdi.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:05:37 by msapin            #+#    #+#             */
/*   Updated: 2023/02/23 14:07:25 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMEHDI_H
# define MINIMEHDI_H

void	display_env(t_msl *ms);
char	**ft_getenv(t_msl *ms);
void	pipe_one(char **args_cmd, t_msl *ms, char **envp);
int		strict_cmp(const char *builts, const char *cmd);
t_var	*getvar(t_msl *ms, char *name);

#endif