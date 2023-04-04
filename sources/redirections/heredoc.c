/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msapin <msapin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 17:44:14 by msapin            #+#    #+#             */
/*   Updated: 2023/04/04 19:37:32 by msapin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// check if heredoc as input return 1 and if heredoc is the last input return 2 else 0
int	is_heredoc(t_block *block)
{
	t_elem	*tmp_arg;
	int		index_here;
	int		index_input;

	index_here = 0;
	index_input = 0;
	if (block->in)
	{
		tmp_arg = block->in;
		while (tmp_arg != NULL)
		{
			index_input++;
			if (tmp_arg->type == HEREDOC)
				index_here = index_input;
			tmp_arg = tmp_arg->next;
		}
		if (index_here == index_input)
			return (2);
		else if (index_here)
			return (1);
	}
	return (0);
}

static char	*input_join(char *input, char const *buf)
{
	char	*tmp_join;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!input)
		tmp_join = malloc(sizeof(char) * (ft_strlen(buf) + 1));
	else
		tmp_join = malloc(sizeof(char) * (ft_strlen(input) \
			+ ft_strlen(buf) + 1));
	if (!tmp_join)
		return (free(tmp_join), \
		tmp_join = NULL, NULL);
	if (input)
	{
		while (input[j])
			tmp_join[i++] = input[j++];
		free(input);
	}
	j = 0;
	while (buf[j])
		tmp_join[i++] = buf[j++];
	tmp_join[i] = '\0';
	return (tmp_join);
}

static char	*get_input(t_msl *ms, t_block *block, t_elem *elem)
{
	char	*tmp_input;

	block->input = NULL;
	tmp_input = NULL;
	while (ft_strmatch(tmp_input, elem->name) == 0)
	{
		tmp_input = readline("> ");
		if (tmp_input == 0)
			return (ft_putstr_fd("minishell: warning: here-document delimited by end-of-file, wanted ", 2), ft_putendl_fd(elem->name, 2), NULL);
		if (ft_strmatch(tmp_input, elem->name) == 0)
		{
			tmp_input = parsing_env_var(ms, tmp_input);
			if (!tmp_input)
				return (NULL);
			tmp_input = ft_strjoin(tmp_input, "\n");	// fix leaks
			if (!block->input)
				block->input = ft_strdup(tmp_input);
			else
				block->input = input_join(block->input, tmp_input);
		}
	}
	return (free(tmp_input), NULL);
}

void	get_heredoc(t_msl *ms, t_block *block, int saveit)
{
	t_elem	*tmp_arg;

	tmp_arg = block->in;
	while (tmp_arg != NULL)
	{
		if (tmp_arg->type == HEREDOC)
			get_input(ms, block, tmp_arg);
		tmp_arg = tmp_arg->next;
	}
	if (saveit == 1)
		free(block->input);
}
