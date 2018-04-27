#include "header.h"

void	*get_new_page(t_block *blocks[], t_type type, size_t size)
{
	t_block *block;
	t_block	*page;

	if ((page = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	page->next = NULL;
	page->space = getpagesize() - sizeof(t_block);
	page->status = 0;
	page->num = 1;
	if (!(block = blocks[type]))
		return (blocks[type] = page);
	while (block->next)
	{
		page->num = block->num > page->num ? block->num : page->num;
		block = block->next;
	}
	page->num++;
	return ((block->next = page));
}


void	*get_free_space(t_block *blocks[], t_type type, size_t size)
{
	t_block	*block;
	t_block *start;
	t_block *new;
	size_t  space;
	int     num;

	if (!(block = blocks[type]))
		return (NULL);
	num = block->num;
	start = NULL;
	space = 0;
	while (block)
	{
		if (block->status || block->num > num)
		{
			start = NULL;
			num = block->num;
			space = 0;
		}
		else
		{
			start = start ? start : block;
			if ((space += block->space + (block->next && block->next->num > block->status ? sizeof(t_block) : 0)) == size)
			{
				start->next = block->next;
				start->status = 1;
				start->space = space;
				return (start);
			}
			if ((int)(space - size - sizeof(t_block)) >= 0)
			{
				new = ((void *)start) + size + sizeof(t_block);
				new->next = block->next;
				new->space = space - size - sizeof(t_block);
				new->status = 0;
				new->num = num;
				start->status = 1;
				start->space = size + sizeof(t_block);
				start->next = new;
				return (start);
			}
		}
		block = block->next;
	}
	return (NULL);
}
