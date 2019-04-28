/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 22:03:06 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/04/27 23:30:55 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stddef.h>

struct							s_md5_digest
{
	unsigned int		a;
	unsigned int		b;
	unsigned int		c;
	unsigned int		d;
};
typedef struct s_md5_digest		t_md5_digest;

typedef struct
{
	size_t						size;
	unsigned char				*msg;
}								t_chunk;

struct							s_md5
{
	size_t						size;
};
typedef struct s_md5			t_md5;

typedef							void (*t_md5_step_helper)
	(t_md5_digest, unsigned int*, unsigned int*, int);

#endif
