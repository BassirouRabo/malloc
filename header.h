#ifndef HEADER_H
# define HEADER_H

# define N 128
# define M 1024
# define IS_TINY(x) (x >= 1 && x <= N)
# define IS_SMALL(x) (x > N && x < M)
# define IS_BIH(x) (x >= M)

// TODO to delete
# include <stdio.h>

# include <stdlib.h>
#include <sys/mman.h>

# include "libft/libft.h"

typedef struct		s_block
{
	struct s_block	*next;
	size_t			space;
	int				status; // 0 free, 1 not free
}					t_block;

typedef enum		e_type
{
					TINY,
					SMALL,
					LARGE
}					t_type;

static t_block		*g_array[3] = {NULL, NULL, NULL};

/*
 ** free.c
 */
void		free(void *ptr);

/*
 ** malloc.c
 */
void		*malloc(size_t size);
void		*malloc_tiny(size_t size);
void		*malloc_small(size_t size);
void		*malloc_big(size_t size);

/*
 ** realloc.c
 */
void		*realloc(void *ptr, size_t size);

/*
 ** print.c
 */
void		show_alloc_mem();

/*
 ** get.c
 */
void	*get_new_page(t_type type, size_t size);
void	*get_free_space(t_type type, size_t size);

/*
 ** util.c
 */

#endif
