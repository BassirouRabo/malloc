#include "shared.h"
#include "header.h"

void		*malloc(size_t size)
{
	void	*ptr;

	if (IS_TINY(size))
	{
		ptr = malloc_tiny(g_blocks, size);
		return (ptr ? ptr + sizeof(t_block) : NULL);
	}
	if (IS_SMALL(size))
	{
		ptr = malloc_small(g_blocks, size);
		return (ptr ? ptr + sizeof(t_block) : NULL);
	}
	if (IS_LARGE(size))
	{
		ptr = malloc_large(g_blocks, size);
		return (ptr ? ptr + sizeof(t_block) : NULL);
	}
	return (NULL);
}

void		*realloc(void *ptr, size_t size)
{
	t_block	*block;

    if (!ptr)
        return (malloc(size));
    if (!size)
    {
        free(ptr);
        return (malloc(1));
    }
	if (!(block = get_block(g_blocks, ptr)))
		return (NULL);
	if (IS_TINY(size))
		dispatch_realloc_tiny(g_blocks, block, ptr, size);
	if (IS_SMALL(size))
		dispatch_realloc_small(g_blocks, block, ptr, size);
	if (IS_LARGE(size))
		dispatch_realloc_large(g_blocks, block, ptr, size);
	return (NULL);
}

void		free(void *ptr)
{
	if (!ptr)
		return ;
	ptr -= sizeof(t_block);
	if (!(free_block(g_blocks, TINY, ptr)))
		if (!(free_block(g_blocks, SMALL, ptr)))
			free_block(g_blocks, LARGE, ptr);
	free_pages(g_blocks);
}

void		show_alloc_mem()
{
	print("TINY", g_blocks[TINY]);
	print("SMALL", g_blocks[SMALL]);
	print("LARGE", g_blocks[LARGE]);
}
