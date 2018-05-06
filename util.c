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

void	*dispatch_realloc_tiny(t_block *blocks[3], t_block	*block, void *ptr, size_t size)
{
	void	*out;

	if (!(block))
		return (NULL);
	if (IS_TINY(block->space) && is_free_space(blocks, TINY, ptr, size))
		return (realloc_tiny(blocks, block, ptr, size));
	if (!(out = malloc(size)))
		return (NULL);
	ft_memcpy(out, ((void *)block + sizeof(t_block)), block->space <= size ? block->space : size);
	block->status = 0;
	free((void *)block);
	return (out);
}

void	*dispatch_realloc_small(t_block *blocks[3], t_block *block, void *ptr, size_t size)
{
	void	*out;

	if (!(block))
		return (NULL);
	if (IS_SMALL(block->space) && is_free_space(blocks, SMALL, ptr, size))
		return (realloc_small(blocks, block, ptr, size));
	if (!(out = malloc(size)))
		return (NULL);
	ft_memcpy(out, ((void *)block + sizeof(t_block)), block->space <= size ? block->space : size);
	block->status = 0;
	free((void *)block);
	printf("#\n");
	return (out);
}

void	*dispatch_realloc_large(t_block *blocks[3], t_block *block, void *ptr, size_t size)
{
	void	*out;

	if (!(block))
		return (NULL);
	if (IS_LARGE(block->space) && is_free_space(blocks, LARGE, ptr, size))
		return (realloc_large(blocks, block, ptr, size));
	if (!(out = malloc(size)))
		return (NULL);
	ft_memcpy(out, ((void *)block + sizeof(t_block)), block->space <= size ? block->space : size);
	block->status = 0;
	free((void *)block);
	return (out);
}
