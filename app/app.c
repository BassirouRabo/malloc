#include <stdio.h>
#include "../header.h"

int main(void)
{/*
	void *ptr1 = malloc(1000);
	void *ptr2 = malloc(1000);
	void *ptr3 = malloc(1000);
	void *ptr4 = malloc(1000);

	void *ptr5 = malloc(1000);
	void *ptr6 = malloc(1000);
	void *ptr7 = malloc(1000);
	void *ptr8 = malloc(1000);

	void *ptr9 = malloc(1000);
	void *ptr10 = malloc(1000);
	void *ptr11 = malloc(1000);
	void *ptr12 = malloc(1000);*/

	/*void *ptr13 = malloc(6000);
	void *ptr14 = malloc(7000);
	void *ptr15 = malloc(9000);
	void *ptr16 = malloc(10000);*/
/*	(void)malloc(1000);
	(void)malloc(1000);*/

/*	free(ptr1);
	free(ptr2);
	free(ptr3);
	free(ptr4);

	free(ptr5);
	free(ptr6);
	free(ptr7);
	free(ptr8);*/

	/*free(ptr13);
	free(ptr14);
	free(ptr15);
	free(ptr16);*/

	void *ptr1 = malloc(50);
	void *ptr2 = malloc(100);
	show_alloc_mem();
	void *ptrr1 = realloc(ptr1, 30);
	printf("###\n");
	show_alloc_mem();
	//free(ptr2);
	//show_alloc_mem();
	return (0);
}
