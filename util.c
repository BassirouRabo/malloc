#include "header.h"

void		*allocate(t_block *blocks[3], size_t size, t_type type)
{
	void    *free_space;
	size_t	len;

	if ((free_space = get_free_space(blocks, type, size)))
		return (free_space);
	len = ((size / (size_t)getpagesize()) * (size_t)getpagesize())
		  + (size % (size_t)getpagesize() ? (size_t)getpagesize() : 0);
	if (!(get_new_page(blocks, type, len)))
		return (NULL);
	return (allocate(blocks, size, type));
}

void	*reallote(t_block *blocks[3], t_block *block, void *ptr, size_t size)
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
		if (space >= size)
			break ;
		space += block->space + sizeof(t_block);
		block = block->next;
	}
	if (space < size)
		return (NULL);
	start->space = size;
	if (space - sizeof(t_block) >= size)
		start->next = new_block_realloc(start, block, space, size);
	return (start);
}

t_block		*new_block_realloc(t_block *start, t_block *block, size_t space, size_t size)
{
	t_block	*new;

	if (!block || !start)
		return (NULL);
	new = start + size;
	new->next = block->next;
	new->status = 0;
	new->num = block->num;
	new->space = space + sizeof(t_block) - size;
	return (new);
}

int     is_free_space(t_block *blocks[], t_type type, void *ptr, size_t size)
{
	t_block	*block;
	size_t 	free_space;

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
