#include "header.h"

void	*get_new_page(void)
{
	void    *str;

	if ((mmap(str, 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	return (str);
}

void	*get_free_space(t_type type, size_t size)
{
	return (NULL);
}
