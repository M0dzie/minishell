/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 17:56:59 by thmeyer           #+#    #+#             */
/*   Updated: 2023/03/01 18:31:29 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_space(char c)
{
    return (c == ' ' || c == '\t');
}

char **ms_split(char *str)
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
