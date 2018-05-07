#include "header.h"

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
