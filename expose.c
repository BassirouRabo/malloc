#include "shared.h"
#include "header.h"

void		*malloc(size_t size)
{
	if (IS_TINY(size))
		return (malloc_tiny(g_blocks, size));
	if (IS_SMALL(size))
		return (malloc_small(g_blocks, size));
	if (IS_BIH(size))
		return (malloc_big(g_blocks, size));
	return (NULL);
}

void		*realloc(void *ptr, size_t size)
{
	return (NULL);
}

void		free(void *ptr)
{
	t_block *tiny;
	t_block *small;
	t_block large;

	if ((tiny = g_blocks[TINY]))
		free_space(g_blocks, TINY, ptr);
	if ((small = g_blocks[SMALL]))
		free_space(g_blocks, SMALL, ptr);
	if ((large = g_blocks[LARGE]))
		free_space(g_blocks, LARGE, ptr);
	return ;
}

void		show_alloc_mem()
{
	print("TINY", g_blocks[TINY]);
	print("SMALL", g_blocks[SMALL]);
	print("LARGE", g_blocks[LARGE]);
}
