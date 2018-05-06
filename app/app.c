#include <stdio.h>
#include "../header.h"

int main(void)
{
	void	*ptr1 = malloc(500);
	void	*ptr2 = malloc(600);
	void	*ptr3 = malloc(700);
	void	*ptr4 = malloc(800);
	void	*ptr5 = malloc(900);
	void	*ptr6 = malloc(1000);
	show_alloc_mem();

	free(ptr1);
/*	free(ptr2);
	free(ptr3);
	free(ptr4);
	free(ptr5);*/
	printf("************\n");
	//void	*ptr7 = realloc(ptr1, 12);
	show_alloc_mem();
	free(ptr2);
	show_alloc_mem();
	return (0);
}
