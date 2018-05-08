/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brabo-hi <brabo-hi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 17:54:05 by brabo-hi          #+#    #+#             */
/*   Updated: 2018/05/07 17:54:44 by brabo-hi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*allocate(t_block *blocks[3], size_t size, t_type type)
{
	void	*free_space;
	size_t	len;

	if ((free_space = get_free_space(blocks, type, size)))
		return (free_space);
	len = ((size / (size_t)getpagesize()) * (size_t)getpagesize())
		+ (size % (size_t)getpagesize() ? (size_t)getpagesize() : 0);
	if (!(get_new_page(blocks, type, len)))
		return (NULL);
	return (allocate(blocks, size, type));
}

void	*reallocate(t_block *block, size_t size)
{
	t_block	*start;
	size_t	space;

	if (!block)
		return (NULL);
	start = block;
	space = block->space;
	block = block->next;
	while (block && !block->status && block->num == start->num)
	{
		space += block->space + sizeof(t_block);
		block = block->next;
	}
	if (space < size)
		return (NULL);
	start->space = size;
	if (space - size >= sizeof(t_block))
		start->next = new_block_realloc(start, block, space, size);
	return ((void *)start + sizeof(t_block));
}

t_block	*new_block_realloc(t_block *start, t_block *block,
	size_t space, size_t size)
{
	t_block	*new;

	if (!start)
		return (NULL);
	new = (void *)start + size + sizeof(t_block);
	new->next = block;
	new->status = 0;
	new->num = start->num;
	new->space = space - size - sizeof(t_block);
	return (new);
}

t_block	*new_block_get_free_space_on_page(t_block *block,
	t_block *start, size_t size, size_t space)
{
	t_block *new;

	new = ((void *)start) + size + sizeof(t_block);
	new->next = block->next;
	new->space = (space - sizeof(t_block)) - size - sizeof(t_block);
	new->status = 0;
	new->num = block->num;
	start->status = 1;
	start->space = size;
	start->next = new;
	return (start);
}

int		is_free_space(t_block *blocks[], t_type type, void *ptr, size_t size)
{
	t_block	*block;
	size_t	free_space;

	free_space = 0;
	block = blocks[type];
	while (block)
	{
		if ((void *)block == ptr)
		{
			free_space += block->space;
			block = block->next;
			while (block && !block->status)
			{
				free_space += block->space;
				block = block->next;
			}
			return (free_space >= size);
		}
		block = block->next;
	}
	return (0);
}
