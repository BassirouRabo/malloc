#include "shared.h"
#include "header.h"

void		*malloc(size_t size)
{
	void	*ptr;

	if (!size)
		return (NULL);
	return ((ptr = allocate(g_blocks, size, get_type(size))) ? ptr + sizeof(t_block) : NULL);
}

void		*realloc(void *ptr, size_t size)
{
	t_block	*out;
	t_block	*block;
	t_type	type;

    if (!ptr)
        return (malloc(size));
    if (!size)
    {
        free(ptr + sizeof(t_block));
        return (malloc(1));
    }
	ptr -= sizeof(t_block);
	if (!(block = get_block(g_blocks, ptr)))
		return (NULL);
	type = get_type(size);
	if (type == get_type(block->space) && is_free_space(g_blocks, type, ptr, size))
		return (reallote(g_blocks, block, ptr, size));
	if (!(out = malloc(size)))
		return (NULL);
	ft_memcpy(out, ((void *)block + sizeof(t_block)), block->space <= size ? block->space : size);
	free((void *)block + sizeof(t_block));
	return (out);
}

void		free(void *ptr)
{
	if (!ptr)
		return ;
	ptr -= sizeof(t_block);
	if (!(free_block(g_blocks, TINY, ptr)))
		if (!(free_block(g_blocks, SMALL, ptr)))
			if (!free_block(g_blocks, LARGE, ptr))
			{
				print_bus_error();
				exit(1);
			}
	free_page(g_blocks, TINY);
	free_page(g_blocks, SMALL);
	free_page(g_blocks, LARGE);
}

void		show_alloc_mem()
{
	print("TINY", g_blocks[TINY]);
	print("SMALL", g_blocks[SMALL]);
	print("LARGE", g_blocks[LARGE]);
}
