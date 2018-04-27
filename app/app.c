#include <stdio.h>
#include "../header.h"

int main(void)
{
    t_block *block = malloc(4);
    t_block *block2 = malloc(6);
    t_block *block3 = malloc(3);

	show_alloc_mem();
	return (0);
}
