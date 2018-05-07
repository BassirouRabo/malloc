#include <stdio.h>
#include "../header.h"

int main(void)
{
	void	*ptr1 = malloc(40);
	void	*ptr2 = malloc(50);
	void	*ptr3 = malloc(60);
	show_alloc_mem();
	void	*ptrr1 = realloc(ptr1, 500);
	printf("****\n");
	show_alloc_mem();
	return (0);
}
