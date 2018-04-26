#include <stdio.h>
#include <unistd.h>
#include "../header.h"

int main(void)
{
	void *str = get_new_page(SMALL, 4);
//	printf("main str[%p]\n",str);
	get_free_space(SMALL, 4);
	return (0);
}