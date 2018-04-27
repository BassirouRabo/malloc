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
# include "struct.h"

/*
 ** free.c
 */
void    free_space(t_block *blocks[], t_type type, void *ptr);

/*
 ** malloc.c
 */
void		*malloc_tiny(t_block *blocks[3], size_t size);
void		*malloc_small(t_block *blocks[3], size_t size);
void		*malloc_big(t_block *blocks[3], size_t size);

/*
 ** realloc.c
 */

/*
 ** print.c
 */
void		print(char *mame, t_block *block);

/*
 ** get.c
 */
void		*get_new_page(t_block *blocks[], t_type type, size_t size);
void		*get_free_space(t_block *blocks[3], t_type type, size_t size);
void		*get_space(t_block *start, size_t size);

/*
 ** util.c
 */

/*
 ** expose.h
 */
void		*malloc(size_t size);
void		*realloc(void *ptr, size_t size);
void		free(void *ptr);
void		show_alloc_mem();

#endif
