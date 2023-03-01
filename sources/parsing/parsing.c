/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:49:26 by thmeyer           #+#    #+#             */
/*   Updated: 2023/03/01 17:31:13 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_args(char ***args)
{
	int i = 0;
	int j = 0;

	while (args[i])
	{
		printf("args[%d]\n", i);
		j = 0;
		while (args[i][j])
			printf("%s\n", args[i][j++]);
		i++;
	}
}

void	count_pipes(t_msl *ms)
{
	int	i;

	i = 0;
	ms->c_pipe = 0;
	while (ms->input[i])
	{
		if (ms->input[i] == '|')
			ms->c_pipe++;
		i++;
	}
	ms->c_cmd = ms->c_pipe + 1;
}

int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

char **my_split(char *str)
{
    int i, j, k, in_quote;
    char **result;
    
    result = (char **)malloc(sizeof(char *) * 256);
    if (!result)
        return (NULL);
    i = 0;
    j = 0;
    k = 0;
    in_quote = 0;
    while (str[i])
    {
        if (str[i] == '"' && (i == 0 || str[i - 1] != '\\'))
            in_quote = !in_quote;
        if (!in_quote && is_space(str[i]))
        {
            if (k > 0)
            {
                result[j] = (char *)malloc(sizeof(char) * (k + 1));
                if (!result[j])
                    return (NULL);
                for (int l = 0; l < k; l++)
                    result[j][l] = str[i - k + l];
                result[j][k] = '\0';
                j++;
                k = 0;
            }
        }
        else
            k++;
        i++;
    }
    if (k > 0)
    {
        result[j] = (char *)malloc(sizeof(char) * (k + 1));
        if (!result[j])
            return (NULL);
        for (int l = 0; l < k; l++)
            result[j][l] = str[i - k + l];
        result[j][k] = '\0';
        j++;
    }
    result[j] = NULL;
    return (result);
}

void	read_prompt(t_msl *ms, char **envp)
{
	int		i;

	i = -1;
	ms->input = ft_strtrim(ms->input, " ");
	count_pipes(ms);
	if (ms->input[0] == '\0' || parsing_errors(ms, ms->input, \
	ms->c_pipe) == -1 || parsing_quotes(ms) == -1)
		return (free(ms->input));
	ms->cmds = ft_calloc(ms->c_pipe + 2, sizeof(char **));
	if (!ms->cmds)
		return (free(ms->input));
	while (++i <= ms->c_pipe)
	{
		ms->split = ft_split(ms->input, '|');
		if (!ms->split)
			return (free(ms->input));
		ms->cmds[i] = my_split(ms->split[i]);
		if (!ms->cmds)
			return (free(ms->input));
	}
	ft_arrfree(ms->split);
	print_args(ms->cmds);
	execution(ms, ms->input, envp);
}
