#include <stdio.h>
#include "../header.h"

int main(void)
{
	(void)malloc(1000);
	(void)malloc(1000);
	(void)malloc(1000);
	(void)malloc(500);
	(void)malloc(1000);
	(void)malloc(100);
/*	(void)malloc(100);
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
	return (0);
}
