#include "header.h"

void		*malloc(size_t size)
{
	if (IS_TINY(size))
		return (malloc_tiny(size));
	if (IS_SMALL(size))
		return (malloc_small(size));
	if (IS_BIH(size))
		return (malloc_big());
	return (NULL);
}

void		*malloc_tiny(size_t size)
{
	void    *free_space;

	if ((free_space = get_free_space(TINY, size)))
		return (free_space);
	add_new_page(TINY);
	return (malloc_tiny(size));
}

void		*malloc_small(size_t size)
{
	void    *free_space;

	if ((free_space = get_free_space(SMALL, size)))
		return (free_space);
	add_new_page(SMALL);
	return (malloc_small(size));
}

void		*malloc_big(void)
{
	return (get_new_page());
}