/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 22:03:06 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/05/04 05:49:22 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "ftstream.h"

# include <stddef.h>

# include "dstring.h"

struct							s_md5_digest
{
	unsigned int		a;
	unsigned int		b;
	unsigned int		c;
	unsigned int		d;
};
typedef struct s_md5_digest		t_md5_digest;

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
typedef void					(*t_print_digest)(t_digest, t_stream);
typedef t_chunk					(*t_reader)(t_stream, size_t size);
typedef t_digest				(*t_hash_func)(t_stream, t_print_digest*);
typedef void					(*t_hash_main)(int, char*[], t_hash_func);
typedef void					(*t_hash_chunk)(unsigned char *, t_digest);

#endif
