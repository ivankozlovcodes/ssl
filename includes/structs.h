/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 22:03:06 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/04/29 11:38:05 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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

typedef struct					s_md5
{
	t_md5_digest				d;
	t_string					*message;
}								t_md5;

typedef struct					s_chunk
{
	size_t						size;
	unsigned char				*msg;
}								t_chunk;

typedef void					(*t_md5_step_helper) (t_md5_digest,
	unsigned int*, unsigned int*, int);

#endif
