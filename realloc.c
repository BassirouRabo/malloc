#include "header.h"

void	*realloc_tiny(t_block *blocks[3], t_block *block, void *ptr, size_t size)
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

void	*realloc_small(t_block *blocks[3], t_block *block, void *ptr, size_t size)
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

void	*realloc_large(t_block *blocks[3], t_block *block, void *ptr, size_t size)
{
	return (NULL);
}
