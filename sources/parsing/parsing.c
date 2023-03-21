/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:49:26 by thmeyer           #+#    #+#             */
/*   Updated: 2023/03/21 17:53:38 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_args(char **args)
{
	for (int i = 0; args[i]; i++)
		printf("token[%d] = %s\n", i, args[i]);
}

void	count_pipes(t_msl *ms)
{
	int	i;

	i = 0;
	ms->c_pipe = 0;
	while (ms->input[i])
	{
		if (ms->input[i] == '\'' || ms->input[i] == '\"')
		{
			check_opened_quotes(ms, ms->input, i + 1, ms->input[i]);
			i = ms->lst_delim;
		}
		if (ms->input[i] == '|')
			ms->c_pipe++;
		i++;
	}
	ms->c_cmd = ms->c_pipe + 1;
}

void	read_prompt(t_msl *ms, char **envp)
{
	int	i;

	i = -1;
	ms->input = ft_strtrim(ms->input, " ");
	if (!ms->input)
		return (free(ms->input));
	count_pipes(ms);
	if (ms->input[0] == '\0' || parsing_errors(ms, ms->input, \
	ms->c_pipe) == -1 || parsing_quotes(ms) == -1)
		return (free(ms->input));
	ms->tokens = ms_strtok(ms, ms->input);
	if (!ms->tokens)
		return (free(ms->input));
	print_args(ms->tokens);
	free(ms->input);
	execution(ms);
}
