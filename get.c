#include "header.h"

void	*get_new_page(t_type type, size_t size)
{
	t_block	*block;
	void	*str;
	void	*page;
	size_t	free_space;

	free_space = getpagesize() - sizeof(t_block);
	if ((str = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	page = str;
	ft_memcpy(str, (void *)0, sizeof(t_block *));
	str += sizeof(t_block *);
	ft_memcpy(str, &free_space, sizeof(size_t));
	str += sizeof(size_t);
	ft_memcpy(str, (void *)0, sizeof(int));
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
	size_t  meta;

	start = NULL;
	space = 0;
    meta = 0;
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
			space += *((size_t *)((void *)block + sizeof(t_block *))) + meta;
            meta = sizeof(t_block);
		}
		if (space >= size)
			return (get_space(start, size)) ;
		block = block->next;
	}
	return (NULL);
}

void	*get_space(t_block *start, size_t size)
{
    t_block *block;
	size_t  space;
    size_t  meta;
    size_t	free_space;

    block = start;
    space = 0;
    meta = 0;
    while (block && !(*((int *)((void *)((size_t *)((void *)block + sizeof(t_block *))) + sizeof(size_t *)))))
    {
        space += *((size_t *)((void *)block + sizeof(t_block *))) + meta;
        meta = sizeof(t_block);
        block = block->next;
        if (space >= size)
            break ;
    }
    if (!start || !block || space < size)
        return (NULL);
    if ((free_space = space - size - sizeof(t_block)) >= 0)
    {
        ft_memcpy(start, ((void *)block) + size, sizeof(t_block *));
        ft_memcpy((start +=  size), (void *)0, sizeof(t_block *));
        ft_memcpy((start += sizeof(t_block *)), &free_space, sizeof(size_t));
        ft_memcpy((start += sizeof(size_t)), (void *)0, sizeof(int));
        return (start + 8);
    }
    return (start + sizeof(t_block));
}
