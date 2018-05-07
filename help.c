#include "header.h"

t_block		*new_block_realloc(t_block *start, t_block *block, size_t space, size_t size)
{
	t_block	*new;

	if (!block || !start)
		return (NULL);
	new = start + size;
	new->next = block->next;
	new->status = 0;
	new->num = block->num;
	new->space = space + sizeof(t_block) - size;
	return (new);
}

t_type		get_type(size_t size)
{
	if (IS_TINY(size))
		return (TINY);
	if (IS_SMALL(size))
		return (SMALL);
	return (LARGE);
}
