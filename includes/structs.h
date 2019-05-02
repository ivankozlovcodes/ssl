/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 22:03:06 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/05/02 12:02:01 by ivankozlov       ###   ########.fr       */
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
	int							last;
	size_t						size;
	unsigned char				*msg;
}								t_chunk;

struct							s_digest
{
	size_t						size;
	unsigned int				*words;
};
typedef struct s_digest			t_digest;

typedef void					(*t_md5_step_helper) (t_md5_digest,
	unsigned int*, unsigned int*, int);

typedef void					(*t_print_digest)(t_digest, t_stream);
typedef t_chunk					(*t_reader)(t_stream, size_t size);
typedef t_digest				(*t_hash_func)(t_stream, t_print_digest*);
typedef void					(*t_hash_main)(int, char*[], t_hash_func);

#endif
