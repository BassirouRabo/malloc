#include <stdio.h>
#include "../header.h"

int main(void)
{
	void * ptr = malloc(1000);
	void *ptr2 = malloc(900);
/*	(void)malloc(1000);
	(void)malloc(500);
	(void)malloc(1000);
	(void)malloc(100);
	(void)malloc(100);
	(void)malloc(1000);
	(void)malloc(1000);
	(void)malloc(1000);
	(void)malloc(1000);
	(void)malloc(1000);
	(void)malloc(1000);
	(void)malloc(1000);
	(void)malloc(1000);
	(void)malloc(1000);*/

	show_alloc_mem();
	//free(ptr);
	//show_alloc_mem();
	free(ptr2);
	show_alloc_mem();
	return (0);
}
