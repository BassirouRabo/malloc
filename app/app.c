#include <stdio.h>
#include <unistd.h>
#include "../header.h"

int main(void)
{
	get_new_page(SMALL, 4);
	void *free = get_free_space(SMALL, 4);
	//printf("mai free[%p]\n", free);

	t_block *block = g_array[SMALL];
	while (block)
	{
		printf("%p\n", (void *)block);
		printf("%zu\n", *((size_t *)(((void *)block) + sizeof(t_block *))));
		printf("%d\n", *((int *)(((void *)block) + sizeof(t_block *) + sizeof(size_t))));
		block = block->next;
	}

	return (0);
}

/*
 void *str = get_new_page(SMALL, 4);
	printf("[%zu][%zu]\n", sizeof(t_block *), sizeof(t_block **));
	printf("BLOCK[%p]\n", str);
	printf("NEXT[%p]\n", *((t_block **)((void *)str)));
	printf("SPACE[%zu]\n", *((size_t *)(((void *)str) + sizeof(t_block *))));
	printf("STATUS[%d]\n", *((int *)(((void *)str) + sizeof(t_block *) + sizeof(size_t))));
	return (0);
 */