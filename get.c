#include "header.h"

void	*get_new_page(t_type type, size_t size)
{
	t_block	*block;
	void	*str;
	void	*page;
	size_t	free_space;

	block = NULL;
	free_space = getpagesize() - sizeof(t_block);
	if ((str = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	page = str;
	ft_memset(str, 0, sizeof(t_block *));
	str += sizeof(t_block *);
	ft_memmove(str, &free_space, sizeof(size_t));
	str += sizeof(size_t);
	ft_memset(str, 0, sizeof(int));
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
	size_t 	remain;

	start = NULL;
	space = 0;
    meta = 0;
	if (!(block = g_array[type]))
		return (NULL);
	while (block)
	{
		printf("#\n");
		printf("NEXT[%p]\n", *((t_block **)((void *)block)));
		printf("SPACE[%zu]\n", *((size_t *)(((void *)block) + sizeof(t_block *))));
		printf("STATUS[%d]\n", *((int *)(((void *)block) + sizeof(t_block *) + sizeof(size_t))));
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
		if ((int)(remain = space - size - sizeof(t_block)) >= 0)
		{
			printf("remain [%zu]\n", remain);
			ft_memmove(start, ((void *)block) + size, sizeof(t_block *));
			ft_memset((start + size), 0, sizeof(t_block *));
			ft_memmove((start ), &remain, sizeof(size_t));
			ft_memset((start + size + sizeof(t_block *) + sizeof(size_t)), 0, sizeof(int));
			//printf("current[%p] next [%p]\n", block, block->next);
			//return (start);
		}
		block = block->next;
	}
	return (NULL);
}
