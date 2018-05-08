/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brabo-hi <brabo-hi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 17:50:54 by brabo-hi          #+#    #+#             */
/*   Updated: 2018/05/07 18:01:25 by brabo-hi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			free_block(t_block *blocks[], t_type type, void *ptr)
{
	t_block *block;

	block = blocks[type];
	while (block)
	{
		if (block == ptr)
		{
			if (!block->status)
			{
				print_double_free();
				exit(1);
			}
			block->status = 0;
			return (1);
		}
		block = block->next;
	}
	return (0);
}

void		free_page(t_block *blocks[], t_type type)
{
	t_block *block;
	t_block *start;
	t_block *prev;

	block = blocks[type];
	prev = NULL;
	while (block)
	{
		start = block;
		while (!block->status && block->next
			&& block->next->num == start->num)
			block = block->next;
		if (!block->next || (!block->status && block->next &&
			block->next->num == start->num + 1))
		{
			free_page_help(blocks, block, type, &prev);
			block = block->next;
			munmap(start, (size_t)getpagesize());
			continue ;
		}
		while (block->next && block->next->num == start->num)
			block = block->next;
		prev = start == blocks[type] ? block : NULL;
		block = block->next;
	}
}

void		free_page_help(t_block *blocks[], t_block *block,
							t_type type, t_block **prev)
{
	if (!*prev)
		blocks[type] = block->next;
	else
		(*prev)->next = block->next;
}
