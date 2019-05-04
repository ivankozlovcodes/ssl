/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 22:03:06 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/05/04 13:34:08 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "ftstream.h"

# include <stddef.h>

# include "dstring.h"

struct							s_algorithm_info
{
	int							chunk_size;
	int							big_endian;
	int							output_size;
	char						*name;
};
typedef struct s_algorithm_info	t_algorithm_info;

typedef struct					s_chunk
{
	size_t						size;
	unsigned char				*msg;
	size_t						max_size;
}								t_chunk;

struct							s_digest
{
	size_t						size;
	unsigned int				*words;
};
typedef struct s_digest			t_digest;

typedef void					(*t_md5_step_helper) (unsigned int *,
	unsigned int*, unsigned int*, int);

typedef t_digest				(*t_init_digest)(void);
typedef void					(*t_hash_chunk)(unsigned char *, t_digest);

#endif
