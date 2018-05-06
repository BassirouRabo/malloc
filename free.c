#include "header.h"

int     free_block(t_block *blocks[], t_type type, void *ptr)
{
	t_block *block;

	block = blocks[type];
	while (block)
	{
		if (block == ptr)
		{
			block->status = 0;
			return (1);
		}
		block = block->next;
	}
	return (0);
}

void    free_pages(t_block *blocks[])
{
	free_page_tiny_small(blocks, TINY);
	free_page_tiny_small(blocks, SMALL);
	free_page_large(blocks);
}

void    free_page_tiny_small(t_block *blocks[], t_type type)
{
	t_block *block;
	t_block *start;
	t_block *prev;

	block = blocks[type];

	prev = NULL;
	while (block)
	{
		start = block;
		while (!block->status && block->next && block->next->num == start->num)
			block = block->next;
		if (!block->next || (!block->status && block->next && block->next->num == start->num + 1))
		{
			if (!prev)
				blocks[type] = block->next;
			else
				prev->next = block->next;
			block = block->next;
			munmap(start, (size_t)getpagesize());
			continue ;
		}
		while (block->next && block->next->num == start->num)
			block = block->next;
		prev = start == blocks[type] ? block : NULL;
		block = block->next;
	}
}

void    free_page_large(t_block *blocks[])
{
	t_block *block;
	t_block *prev;
	t_block *next;

	block = blocks[LARGE];
	while (block && !block->status)
	{
		blocks[LARGE] = block->next;
		munmap(block, block->space);
		block = blocks[LARGE];
	}
	while (block)
	{
		prev = block;
		if (block->next && !block->next->status)
		{
			next = block->next->next;
			munmap(block->next, block->next->space);
			block = next;
			prev->next = next;
		}
		else
			block = block->next;
	}
}