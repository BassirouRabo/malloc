#ifndef STRUCT_H
# define STRUCT_H

# include <stdio.h>

typedef struct		s_block
{
	struct s_block	*next;
	size_t			space;
	int				status;
	int				num;
}					t_block;

typedef enum		e_type
{
	TINY,
	SMALL,
	LARGE
}					t_type;

#endif
