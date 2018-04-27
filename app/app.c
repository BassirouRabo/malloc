#include <stdio.h>
#include "../header.h"

int main(void)
{
    t_block *block = malloc(4);
    t_block *block2 = malloc(6);
    t_block *block3 = malloc(3);


	//t_block *block = g_array[TINY];
	//t_block *block = free;
	while (block)
	{
        printf("CURRENT[%p]\n", block);
        printf("NEXT[%p]\n", *((t_block **)((void *)block)));
        printf("SPACE[%zu]\n", *((size_t *)(((void *)block) + sizeof(t_block *))));
        printf("STATUS[%d]\n\n", *((int *)(((void *)block) + sizeof(t_block *) + sizeof(size_t))));
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