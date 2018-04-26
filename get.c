#include "header.h"

void *get_space(t_block *pBlock, t_type type, size_t size);

void	*get_new_page(t_type type, size_t size)
{
	t_block	*block;
	void	*str;
	void	*page;
	int		status;
	size_t	free_space;

	status = 1;
	free_space = getpagesize() - sizeof(t_block);
	if ((str = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	page = str;
	ft_memcpy(str, str + sizeof(t_block), sizeof(t_block *));
	str += sizeof(t_block *);
	ft_memcpy(str, &free_space, sizeof(size_t));
	str += sizeof(size_t);
	ft_memcpy(str, &status, sizeof(int));
	while ((block = g_array[type]) && block->next)
		block = block->next;
	if (!block)
		return (g_array[type] = page);
	else
		return (block->next = page);
}

void	*get_free_space(t_type type, size_t size)
{
	t_block	*block;
	t_block	*start;
	size_t	space;

	start = NULL;
	space = 0;
	if (!(block = g_array[type]))
		return (NULL);
	while (block)
	{
		if (*((int *)((void *)((size_t *)((void *)block + sizeof(t_block *))) + sizeof(size_t *))))
		{
			start = NULL;
			space = 0;
		}
		else
		{
			start = start ? start : block;
			space += *((size_t *)((void *)block + sizeof(t_block *)));
		}
		if (space >= size)
			return (get_space(start, type, size)) ;
		block = block->next;
	}
	return (NULL);
}

void	*get_space(t_block *start, t_type type, size_t size)
{
	size_t space;

	if ((space = *((size_t *)((void *)start + sizeof(t_block *)))) < size)
	return NULL;

}
