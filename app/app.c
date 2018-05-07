#include <stdio.h>
#include "../header.h"

int main(void)
{
	void	*ptr1 = malloc(5000);
	void	*ptr2 = malloc(6000);
	void	*ptr3 = malloc(7000);
	show_alloc_mem();
	void	*ptrr1 = realloc(ptr1, 50);
	void	*ptrr2 = realloc(ptrr1, 10);
	printf("****\n");
	show_alloc_mem();
	return (0);
}
