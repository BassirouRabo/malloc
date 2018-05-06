#include "header.h"

void	print(char *name, t_block *block)
{
	if (name && block)
	{
		printf("\t%s\n", name);
		while (block)
		{
			printf("CURRENT[%p]\n", block);
			printf("NEXT[%p]\n", block->next);
			printf("SPACE[%zu]\n",block->space);
			printf("NUM[%d]\n", block->num);
			if ( block->status)
				printf("USED\n");
			else
				printf("FREE\n");
			printf("\n");
			block = block->next;
		}
	}
}

void	print_double_free(void)
{
	ft_putstr("Error double free\n");
}

void	print_bus_error(void)
{
	ft_putstr("Bus error\n");
}
