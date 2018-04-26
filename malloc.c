#include "header.h"

void		*malloc(size_t size)
{
	if (IS_TINY(size))
		return (malloc_tiny(size));
	if (IS_SMALL(size))
		return (malloc_small(size));
	if (IS_BIH(size))
		return (malloc_big(size));
	return (NULL);
}

void		*malloc_tiny(size_t size)
{
	void    *free_space;

	if ((free_space = get_free_space(TINY, size)))
		return (free_space);
	if (!(get_new_page(TINY, size)))
		return (NULL);
	return (malloc_tiny(size));
}

void		*malloc_small(size_t size)
{
	void    *free_space;

	if ((free_space = get_free_space(SMALL, size)))
		return (free_space);
	if (!(get_new_page(SMALL, size)))
		return (NULL);
	return (malloc_small(size));
}

void		*malloc_big(size_t size)
{
	return (get_new_page(LARGE, size));
}
