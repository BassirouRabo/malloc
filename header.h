#ifndef HEADER_H
# define HEADER_H

# define N 128
# define M 1024
# define IS_TINY(x) (x >= 1 && x <= N)
# define IS_SMALL(x) (x > N && x < M)
# define IS_LARGE(x) (x >= M)

// TODO to delete
# include <stdio.h>

# include <stdlib.h>
#include <sys/mman.h>

# include "libft/libft.h"
# include "struct.h"

/*
 ** free.c
 */
int		free_block(t_block *blocks[], t_type type, void *ptr);
void	free_pages(t_block *blocks[]);
void	free_page_tiny_small(t_block *blocks[], t_type type);
void	free_page_large(t_block *blocks[]);


/*
 ** malloc.c
 */
void		*allocate(t_block *blocks[3], size_t size, t_type type);

/*
 ** realloc.c
 */
void	*realloc_tiny(t_block *blocks[3], t_block *block, void *ptr, size_t size);
void	*realloc_small(t_block *blocks[3], t_block *block, void *ptr, size_t size);
void	*realloc_large(t_block *blocks[3], t_block *block, void *ptr, size_t size);

/*
 ** print.c
 */
void	print(char *mame, t_block *block);
void	print_double_free(void);
void	print_bus_error(void);

/*
 ** get.c
 */
void	*get_new_page(t_block *blocks[], t_type type, size_t size);
void	*get_free_space(t_block *blocks[3], t_type type, size_t size);
void	*get_free_space_on_page(t_block *block, size_t size, int num);
t_block	*get_block(t_block *blocks[], void *ptr);

/*
 ** expose.h
 */
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	free(void *ptr);
void	show_alloc_mem();

/*
 ** util.c
 */
int		is_free_space(t_block *blocks[], t_type type, void *ptr, size_t size);
void	*dispatch_realloc_tiny(t_block *blocks[3], t_block *block, void *ptr, size_t size);
void	*dispatch_realloc_small(t_block *blocks[3], t_block *block, void *ptr, size_t size);
void	*dispatch_realloc_large(t_block *blocks[3], t_block *block, void *ptr, size_t size);

/*
 ** help.c
 */
t_block		*new_block_realloc(t_block *start, t_block *block, size_t space, size_t size);
t_type		get_type(size_t size);

#endif
