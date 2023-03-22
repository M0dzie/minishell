/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 17:02:51 by mehdisapin        #+#    #+#             */
/*   Updated: 2023/03/21 07:22:09 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	elem_addback(t_elem **stack, t_elem *new_elem)
{
	t_elem	*addback;

	if (!(*stack))
		*stack = new_elem;
	else
	{
		addback = (*stack);
		while (addback->next != NULL)
			addback = addback->next;
		addback->next = new_elem;
	}
}

t_elem	*new_elem(char *name, int type)
{
	t_elem	*new_elem;

	new_elem = malloc(sizeof(t_elem));
	if (!new_elem)
		return (display_error_exec("bash: ", "new_elem", 15), NULL);
	new_elem->name = ft_strdup_null(name);
	new_elem->type = type;
	new_elem->next = NULL;
	return (new_elem);
}

void	fill_blocks(t_msl *ms)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i <= ms->c_pipe)
	{
		while (ms->tokens[++j])
		{
			if (ft_strmatch(ms->tokens[j], "|"))
				break;
			else if (ft_strmatch(ms->tokens[j], "<") && ms->tokens[j + 1])
				elem_addback(&ms->blocks[i]->in, new_elem(ms->tokens[++j], INPUT));
			else if (ft_strmatch(ms->tokens[j], "<<") && ms->tokens[j + 1])
				elem_addback(&ms->blocks[i]->in, new_elem(ms->tokens[++j], HEREDOC));
			else if (ft_strmatch(ms->tokens[j], ">") && ms->tokens[j + 1])
				elem_addback(&ms->blocks[i]->out, new_elem(ms->tokens[++j], TRUNC));
			else if (ft_strmatch(ms->tokens[j], ">>") && ms->tokens[j + 1])
				elem_addback(&ms->blocks[i]->out, new_elem(ms->tokens[++j], APPEND));
			else if (!ms->blocks[i]->cmd_found)
			{
				elem_addback(&ms->blocks[i]->arg, new_elem(ms->tokens[j], CMD));
				ms->blocks[i]->cmd_found = 1;
			}
			else
				elem_addback(&ms->blocks[i]->arg, new_elem(ms->tokens[j], ARG));
		}
	}
}

void	malloc_pipe(t_msl *ms)
{
	int	i;

	i = 0;
	ms->pipes = ft_calloc(ms->c_pipe, sizeof(int *));
	if (!ms->pipes)
		display_error_exec("bash: ", "pipes", 15);
	while (i < ms->c_pipe)
	{
		ms->pipes[i] = ft_calloc(2, sizeof(int));
		if (!ms->pipes[i])
			display_error_exec("bash: ", "pipex[i]", 15);
		pipe(ms->pipes[i]);
		i++;
	}
}

void	parsing_exec(t_msl *ms)
{
	int	i;
	int	j;

	ms->blocks = ft_calloc(ms->c_pipe + 2, sizeof(t_block *));
	if (!ms->blocks)
		display_error_exec("bash: ", "ms->blocks", 15);
	i = -1;
	j = -1;
	while (++i <= ms->c_pipe)
	{
		ms->blocks[i] = malloc(sizeof(t_block));
		if (!ms->blocks[i])
			display_error_exec("bash: ", "ms->blocks[i]", 15);
		ms->blocks[i]->arg = NULL;
		ms->blocks[i]->in = NULL;
		ms->blocks[i]->out = NULL;
		ms->blocks[i]->input = NULL;
		ms->blocks[i]->index = i;
		ms->blocks[i]->cmd_found = 0;
	}
	ms->pid = ft_calloc(ms->c_cmd, sizeof(pid_t));
	if (!ms->pid)
		display_error_exec("bash: ", "pid", 15);
	malloc_pipe(ms);
	fill_blocks(ms);
}