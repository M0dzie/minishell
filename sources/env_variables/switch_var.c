/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 09:35:45 by thmeyer           #+#    #+#             */
/*   Updated: 2023/03/08 10:37:20 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_sign(char *token, int i)
{
	while (token[i] && token[i] != '\"')
	{
		if (token[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*get_value(t_msl *ms, char *token)
{
	int		i;
	char	**test;

	i = 0;
	test = ft_split(token, '$');
	for (int j = 0; test[j]; j++)
		printf("%s\n", test[j]);
	printf("clean var = %s\n", token);
	// if (ft_isalpha(token[i]))
	// 	recup dans env;
	if (token[i] == '$' || token[i] == ' ')
		return ("$");
	if (token[i] == '?')
		ft_itoa(ms->status);
	return ("Salut");
	// return la valeur de env meme si c'est NULL
}

char	*switch_var(t_msl *ms, char *token, int i)
{
	int		is_quote;
	char	*var;
	char	*before;
	char	*next;

	is_quote = 0;
	if (token[i] == '\"')
		is_quote = 1;
	while (token[i] != '$')
		i++;
	// mix de malloc ?
	before = get_before_quote(token, i);
	if (!before)
		return (NULL);
	printf("before = %s\n", before);
	var = get_value(ms, token + i + 1);
	if (!var)
		return (free(before), NULL);
	i++;
	while (token[i] && ((is_quote && token[i] != '\"' && token[i] != '\'') \
	|| (!is_quote && token[i] != ' ')))
		i++;
	next = get_after_quote(token, i);
	if (!next)
		return (free(before), free(var), NULL);
	printf("next = %s\n", next);
	var = clear_line(before, var, next);
	if (!var)
		return (free(before), free(next), NULL);
	printf("var = %s\n", var);
	return (free(before), free(next), var);
}
