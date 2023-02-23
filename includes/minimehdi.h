/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimehdi.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:05:37 by msapin            #+#    #+#             */
/*   Updated: 2023/02/23 18:39:36 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMEHDI_H
# define MINIMEHDI_H

void	display_env(t_msl *ms);
char	**ft_getenv(t_msl *ms);
void	pipe_one(char **args_cmd, t_msl *ms, char **envp);
int		strict_cmp(const char *builts, const char *cmd);
t_var	*getvar(t_msl *ms, char *name);
char	**split_equal(char *env_var);
void	var_add_back(t_msl *ms, t_var *var);
t_var	*new_var(char *name, char *value);

#endif