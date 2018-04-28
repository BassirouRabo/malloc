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
//	free_page(blocks, TINY);
	free_page(blocks, SMALL);
//	free_page(blocks, LARGE);
}

void    free_page(t_block *blocks[], t_type type)
{
	t_block *block;
	t_block *start;
	t_block *prev;
	//show_alloc_mem();
	block = blocks[type];
	prev = NULL;
	while (block)
	{
		printf("#[%p]\n", block);
		start = block;
		while (!block->status && block->next && block->next->num == start->num)
		{
			printf("**\n");
			block = block->next;
		}
		printf("**[%p]\n", block->next);
		if (!block->next || (block->next && block->next->num == start->num + 1))
		{
			printf("*\n");
			munmap(start, (size_t)getpagesize());
			if (!prev)
				blocks[type] = block->next;
			else
				prev->next = block->next;
		}
		while (block->next && block->next->num == start->num)
			block = block->next;
		prev = start == blocks[type] ? block : NULL;
		block = block->next;
	}
}
