/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:56:59 by thmeyer           #+#    #+#             */
/*   Updated: 2023/03/02 09:57:30 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	count_tokens(char *input)
{
	int		i;
	int		n_tok;

	i = -1;
	n_tok = 0;
	while (input[++i])
	{
		if ((input[i] != '\'' && input[i] != '\"' && input[i] != ' ') \
		&& (input[i + 1] == '\0' || input[i + 1] == '\'' || \
		input[i + 1] == '\"' || input[i + 1] == ' '))
			n_tok++;
	}
	return (n_tok);
}

int	token_len(char *input, char sep, int i)
{
	int	len;

	len = 0;
	while (input[i] != sep && input[i])
	{
		len++;
		i++;
	}
	printf("len = %d\n", len + 1);
	return (len + 1);
}

char	**ms_split(char *input)
{
	int	i;
	int	j;
	int	k;
	// int		in_quote;
    char	**split;

	split = ft_calloc((count_tokens(input) + 1), sizeof(char *));
	if (!split)
		return (NULL);
	i = -1;
	j = 0;
	k = 0;
	// in_quote = 0;
	while (input[++i])
	{
		// if ((input[i] == '\"' || input[i] == '\'') && (i == 0 \
		|| input[i - 1] != '\\'))
		if (input[i] == '\"' || input[i] == '\'')
		{
			i += token_len(input, input[i], i + 1);
			// in_quote = !in_quote;
		}
        // if (!in_quote && is_space(input[i]))
        if (is_space(input[i]))
        {
            if (k > 0)
            {
                split[j] = ft_calloc((k + 1), sizeof(char));
                if (!split[j])
                    return (NULL);
                for (int l = 0; l < k; l++)
                    split[j][l] = input[i - k + l];
                j++;
                k = 0;
            }
        }
        else
            k++;
    }
    if (k > 0)
    {
        split[j] = ft_calloc((k + 1), sizeof(char));
        if (!split[j])
            return (NULL);
        for (int l = 0; l < k; l++)
            split[j][l] = input[i - k + l];
        j++;
    }
    return (split);
}
