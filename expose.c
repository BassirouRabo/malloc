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
	return ;
}

void		show_alloc_mem()
{
	print("TINY", g_blocks[TINY]);
	print("SMALL", g_blocks[SMALL]);
	print("LATGE", g_blocks[LARGE]);
}
