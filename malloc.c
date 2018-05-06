#include "header.h"

void		*malloc_tiny(t_block *blocks[3], size_t size)
{
	void    *free_space;

    if ((free_space = get_free_space(blocks, TINY, size)))
        return (free_space);
    if (!(get_new_page(blocks, TINY, (size_t)getpagesize())))
        return (NULL);
	return (malloc_tiny(blocks, size));
}

void		*malloc_small(t_block *blocks[3], size_t size)
{
	void    *free_space;

	if ((free_space = get_free_space(blocks, SMALL, size)))
		return (free_space);
	if (!(get_new_page(blocks, SMALL, (size_t)getpagesize())))
		return (NULL);
	return (malloc_small(blocks, size));
}

void		*malloc_large(t_block *blocks[3], size_t size)
{
	t_block    *page;
	t_block *block;

	if ((page = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	block = blocks[LARGE];
	page->next = NULL;
	page->space = size - sizeof(t_block);
	page->status = 1;
	page->num = 1;
	if (!block)
		return ((void *)(blocks[LARGE] = page));
	page->num = block->num;
	while (++page->num && block->next)
		block = block->next;
	block->next = page;
	return ((void *)page);
}
