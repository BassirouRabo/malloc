#ifndef HEADER_H
# define HEADER_H

// TODO to delete
# include <stdio.h>

# include <stdlib.h>
#include <sys/mman.h>

# include "libft/libft.h"

typedef struct		s_block
{
	size_t			size;
	int				status;
	struct s_block	*next;
}					t_block;

t_block		g_array[3] = {NULL, NULL, NULL};

void		free(void *ptr);
void		*malloc(size_t size);
void		*realloc(void *ptr, size_t size);
void		show_alloc_mem();

#endif
