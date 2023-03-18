/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 19:28:54 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/03/18 20:56:42 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_onlynum(char *arg)
{
	int	i;
	int	lenstr;

	i = -1;
	lenstr = ft_strlen(arg);
	if (lenstr == 1 && (arg[0] == '-' || arg[0] == '+'))
		return (0);
	else if (lenstr > 1)
	{
		if (arg[0] == '-' || arg[0] == '+')
			i++;
	}
	while (arg[++i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
	}
	return (1);
}

void	display_exit(t_msl *ms, int exit_nb, int num_error, char *arg)
{
	if (num_error > 0)
	{
		if (ms->c_pipe == 0)
			ft_putendl_fd("exit", 2);
		display_error_exec("bash: exit: ", arg, num_error);
	}
	else
	{
		if (ms->c_pipe == 0)
			ft_putendl_fd("exit", 1);
	}
	exit (exit_nb);
}

long	ft_atolong(const char *str)
{
	long long	i;
	int			sign;
	long long	return_int;

	i = 0;
	sign = 1;
	return_int = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 43 || str[i] == 45)
	{
		if (str[i] == 45)
			sign = -1;
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57 && str[i] != '\0')
	{
		if (return_int != (return_int * 10 + ((str[i] - 48) * sign)) / 10)
			return ((sign + 1) / 2 / -1);
		return_int = return_int * 10 + (str[i] - 48) * sign;
		i++;
	}
	return (return_int);
}

int	is_toolong(t_msl *ms, char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (len > 20)
		display_exit(ms, 2, 11, arg);
	if (arg[0] == '-')
	{
		if (len == 20)
		{
			if (ft_strncmp(arg, "-9223372036854775808", 20) > 0)
				display_exit(ms, 2, 11, arg);
		}
	}
	else
	{
		if (len == 19)
		{
			if (ft_strncmp(arg, "9223372036854775807", 19) > 0)
				display_exit(ms, 2, 11, arg);
		}
		else if (len == 20)
			display_exit(ms, 2, 11, arg);
	}
	return (0);
}

void	exec_exit(t_msl *ms, char **args_cmd)
{
	if (ft_arrlen(args_cmd) > 2)
	{
		if (is_onlynum(args_cmd[1]))
			display_exit(ms, 1, 10, NULL);
		else
			display_exit(ms, 2, 11, args_cmd[1]);
	}
	else if (ft_arrlen(args_cmd) == 2)
	{
		if (is_onlynum(args_cmd[1]))
		{
			if (!is_toolong(ms, args_cmd[1]))
				display_exit(ms, ft_atolong(args_cmd[1]), 0, NULL);
		}
		else
			display_exit(ms, 2, 11, args_cmd[1]);
	}
	else
		display_exit(ms, 0, 0, NULL);
}

// void	exec_exit(t_msl *ms, char **args_cmd)
// {
// 	if (ms->c_pipe == 0)
// 	{	
// 		if (ft_arrlen(args_cmd) > 2)
// 		{
// 			if (is_onlynum(args_cmd[1]))
// 				display_exit(ms, 1, 10, NULL);
// 			else
// 				display_exit(ms, 2, 11, args_cmd[1]);
// 		}
// 		else if (ft_arrlen(args_cmd) == 2)
// 		{
// 			if (is_onlynum(args_cmd[1]))
// 			{
// 				if (!is_toolong(ms, args_cmd[1]))
// 					display_exit(ms, ft_atolong(args_cmd[1]), 0, NULL);
// 			}
// 			else
// 				display_exit(ms, 2, 11, args_cmd[1]);
// 		}
// 		else
// 			display_exit(ms, 0, 0, NULL);
// 	}
// }
