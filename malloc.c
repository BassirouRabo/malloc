#include "header.h"

void		*malloc_tiny(t_block *blocks[3], size_t size)
{
	void    *free_space;

    if ((free_space = get_free_space(blocks, TINY, size)))
        return (free_space);
    if (!(get_new_page(blocks, TINY, size)))
        return (NULL);
	return (malloc_tiny(blocks, size));
}

void		*malloc_small(t_block *blocks[3], size_t size)
{
	void    *free_space;

	if ((free_space = get_free_space(blocks, SMALL, size)))
		return (free_space);
	if (!(get_new_page(blocks, SMALL, size)))
		return (NULL);
	return (malloc_small(blocks, size));
}

void		*malloc_big(t_block *blocks[3], size_t size)
{
	t_block    *page;

	if (!(page = (t_block *)get_new_page(blocks, LARGE, size)))
		return (NULL);
	page->status = 1;
	return ((void *)page);
}
