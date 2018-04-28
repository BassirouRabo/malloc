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
	free_page(blocks, TINY);
	free_page(blocks, SMALL);
	free_page(blocks, LARGE);
}

void    free_page(t_block *blocks[], t_type type)
{
	t_block *block;
	t_block *start;
	t_block *prev;

	block = blocks[type];
	start = block;
	prev = NULL;
	while (block)
	{
		if (start && block->next && (int)(block->next->num > block->num))
		{
			munmap(start, (size_t)getpagesize());
			start = block->next;
			if (!prev)
			{
				blocks[type] = block->next;
				prev = NULL;
			}
			else
			{
				prev->next = block->next;
				prev = block;
			}
		}
		else if (block->status)
		{
			start = NULL;
			prev = block;
		}
		else if (!(block->status))
		{
			
		}
		block = block->next;
	}



	while (block)
	{
		if (block->next && (int)(block->next->num > start->num))
		{
			munmap(start, type == LARGE ? start->space : (size_t)getpagesize());
			if (start == first)
			{
				start = block->next;
				blocks[type] = block->next;
				first = block->next;
			}
			else
			{
				start->next = block->next;
				start = block->next;
			}


		}
		block = block->next;
	}
}