/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brabo-hi <brabo-hi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 17:48:59 by brabo-hi          #+#    #+#             */
/*   Updated: 2018/05/07 17:50:23 by brabo-hi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
				total += block->space;
			printf("%p - %p : %zu octets | Page : [%d] | Status : [%s]\n",
				((void *)block + sizeof(t_block)), ((void *)block->next
				+ sizeof(t_block)), block->space, block->num, block->status
				? "USED" : "FREE");
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
