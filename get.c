#include "header.h"

void	*get_new_page(t_block *blocks[], t_type type, size_t size)
{
	t_block *block;
	t_block	*page;

	if ((page = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0)) == MAP_FAILED)
		return (NULL);
	page->next = NULL;
	page->space = size - sizeof(t_block);
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
	t_block *block;
	t_block *start;
	int     num;

	if (!(block = blocks[type]))
		return (NULL);
	while (block)
	{
		num = block->num;
		if ((start = get_free_space_on_page(block, size, num)))
			return (start);
		while (block && block->num == num)
			block = block->next;
	}
	return (NULL);
}

void    *get_free_space_on_page(t_block *block, size_t size, int num)
{
	t_block *start;
	size_t  space;
	t_block *new;

	start = NULL;
	space = 0;
	while (block && block->num == num)
	{
		if (!block->status)
		{
			start = start ? start : block;
			space += block->space + sizeof(t_block);
			if (space - sizeof(t_block) == size)
			{
				start->status = 1;
				return (start);
			}
			else if ((space - sizeof(t_block)) >=  size + sizeof(t_block))
			{
				new = ((void *)start) + size + sizeof(t_block);
				new->next = block->next;
				new->space = (space - sizeof(t_block)) - size - sizeof(t_block);
				new->status = 0;
				new->num = num;
				start->status = 1;
				start->space = size + sizeof(t_block);
				start->next = new;
				return (start);
			}
		}
		else
		{
			start = NULL;
			space = 0;
		}
		block = block->next;
	}
	return (NULL);
}
