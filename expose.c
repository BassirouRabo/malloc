#include "shared.h"
#include "header.h"

void		*malloc(size_t size)
{
	if (IS_TINY(size))
		return (malloc_tiny(g_blocks, size));
	if (IS_SMALL(size))
		return (malloc_small(g_blocks, size));
	if (IS_LARGE(size))
		return (malloc_large(g_blocks, size));
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
