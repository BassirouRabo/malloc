#include "header.h"

void		*allocate(t_block *blocks[3], size_t size, t_type type)
{
	void    *free_space;
	size_t	len;

	if ((free_space = get_free_space(blocks, type, size)))
		return (free_space);
	len = ((size / (size_t)getpagesize()) * (size_t)getpagesize())
		  + (size % (size_t)getpagesize() ? (size_t)getpagesize() : 0);
	if (!(get_new_page(blocks, type, len)))
		return (NULL);
	return (allocate(blocks, size, type));
}
