#include "header.h"

void    print(char *name, t_block *block)
{
	if (name && block)
	{
		printf("%s\n", name);
		while (block)
		{
			printf("CURRENT[%p]\n", block);
			printf("NEXT[%p]\n", *((t_block **)((void *)block)));
			printf("SPACE[%zu]\n", *((size_t *)(((void *)block) + sizeof(t_block *))));
			printf("STATUS[%d]\n\n", *((int *)(((void *)block) + sizeof(t_block *) + sizeof(size_t))));
			block = block->next;
		}
	}
}