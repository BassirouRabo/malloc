#include "header.h"

char	*get_page(void)
{
	void    *str;

	if ((mmap(str, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	return (str);
}