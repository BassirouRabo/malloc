#include "header.h"


void	print(char *name, t_block *block)
{
	size_t	total;

	total = 0;
	if (name && block)
	{
		printf("%s : %p\n", name, block);
		while (block)
		{
			if (!block->status)
			{
				total += block->space;
				printf("%p - %p : %zu octets [%d][%s]\n", ((void *)block + sizeof(t_block)), ((void *)block->next + sizeof(t_block)), block->space, block->num, block->status ? "USED" : "FREE");
			}
			else
			{
				total += block->space;
				printf("%p - %p : %zu octets [%d][%s]\n", ((void *)block + sizeof(t_block)), ((void *)block->next + sizeof(t_block)), block->space, block->num, block->status ? "USED" : "FREE");
			}
			block = block->next;
		}
		printf("Total : %zu octets\n", total);
	}
}

void	print_double_free(void)
{
	ft_putstr("Error double free\n");
}

void	print_bus_error(void)
{
	ft_putstr("The pointer wasn't allocated\n");
}
