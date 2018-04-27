#include "header.h"

void	*get_new_page(t_type type, size_t size)
{
	t_block	*block;
	void	*str;
	void	*page;
	size_t	free_space;
printf("NEW\n");
	free_space = getpagesize() - sizeof(t_block);
	if ((str = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	page = str;
	ft_memset(str, 0, sizeof(t_block *));
	str += sizeof(t_block *);
	ft_memmove(str, &free_space, sizeof(size_t));
	str += sizeof(size_t);
	ft_memset(str, 0, sizeof(int));
    g_array[0] = (t_block *)page;
    return (g_array[type]);
	while ((block = g_array[type]) && block->next)
		block = block->next;
	if (!block)
    {
        printf("NUL [%d - %zu]\n", type, ((t_block *)page)->space);
        g_array[type] = page;
        if (!g_array[type])
            printf("NO\n");
        return (g_array[type]);
    }
	else
    {
        printf("NOT NUL\n");
        return (block->next = page);
    }
}

void	*get_free_space(t_type type, size_t size)
{
	t_block	*block;
	t_block	*start;
    t_block *new;
	size_t	space;
	size_t  meta;
	size_t 	remain;

	start = NULL;
	space = 0;
    meta = 0;
	if (!(block = g_array[type]))
		return (NULL);
	while (block)
	{
		if (*((int *)(((void *)block) + sizeof(t_block *) + sizeof(size_t))))
		{
			start = NULL;
			space = 0;
		}
		else
		{
			start = start ? start : block;
			space += *((size_t *)(((void *)block) + sizeof(t_block *))) + meta;
            meta = sizeof(t_block);
		}
		if (start && (int)(remain = space - size - sizeof(t_block)) >= 0)
		{
            new = ((void *)start) + size + sizeof(t_block);
            //printf("start [%p] new[%p]\n", start, new);
            new->next = block->next;
            new->space = remain;
            new->status = block->status;
            start->next = new;
            start->status = 1;
            return (start);
		}
		block = block->next;
	}
	return (NULL);
}
