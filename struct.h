/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brabo-hi <brabo-hi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 17:54:00 by brabo-hi          #+#    #+#             */
/*   Updated: 2018/05/07 17:54:01 by brabo-hi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
