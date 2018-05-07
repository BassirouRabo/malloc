#include <stdio.h>
#include "../header.h"

int main(void)
{
	void	*ptr0 = malloc(200);
	void	*ptr1 = malloc(300);
	void	*ptr2 = malloc(400);
	void	*ptr3 = malloc(500);
//	free(ptr1);
	free(ptr2);
	show_alloc_mem();
	void	*ptrr1 = realloc(ptr1, 150);
	printf("**** ptrr1[%p]\n", ptrr1);
//	show_alloc_mem();
	free(ptrr1);
	free(ptr3);
	free(ptr0);
	//void	*ptrr2 = realloc(ptrr1, 10);
	printf("****\n");
	show_alloc_mem();
	return (0);
}
