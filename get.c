/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brabo-hi <brabo-hi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 17:51:29 by brabo-hi          #+#    #+#             */
/*   Updated: 2018/05/07 17:53:04 by brabo-hi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*get_new_page(t_block *blocks[], t_type type, size_t size)
{
	t_block *block;
	t_block	*page;

	if ((page = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON |
		MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	page->next = NULL;
	page->space = size - sizeof(t_block);
	page->status = 0;
	page->num = 1;
	if (!(block = blocks[type]))
		return (blocks[type] = page);
	while (block->next)
	{
		page->num = block->num > page->num ? block->num : page->num;
		block = block->next;
	}
	page->num++;
	return ((block->next = page));
}

void	*get_free_space(t_block *blocks[], t_type type, size_t size)
{
	t_block *block;
	t_block *start;
	int		num;

	if (!(block = blocks[type]))
		return (NULL);
	while (block)
	{
		num = block->num;
		if ((start = get_free_space_on_page(block, size, num)))
			return (start);
		while (block && block->num == num)
			block = block->next;
	}
	return (NULL);
}

void	*get_free_space_on_page(t_block *block, size_t size, int num)
{
	t_block	*start;
	size_t	space;

	start = NULL;
	space = 0;
	while (block && block->num == num)
	{
		if (!block->status)
		{
			start = start ? start : block;
			space += block->space + sizeof(t_block);
			if ((space - sizeof(t_block) == size) && (start->status = 1))
				return (start);
			else if ((space - sizeof(t_block)) - sizeof(t_block) >= size)
				return (new_block_get_free_space_on_page(block,
					start, size, space));
		}
		else
		{
			start = NULL;
			space = 0;
		}
		block = block->next;
	}
	return (NULL);
}

t_block	*get_block(t_block *blocks[], void *ptr)
{
	t_block *block;
	int		i;

	i = 0;
	while (i < 3)
	{
		block = blocks[i++];
		while (block)
		{
			if ((void *)block == ptr)
				return (block);
			block = block->next;
		}
	}
	return (NULL);
}

t_type	get_type(size_t size)
{
	if (IS_TINY(size))
		return (TINY);
	if (IS_SMALL(size))
		return (SMALL);
	return (LARGE);
}
