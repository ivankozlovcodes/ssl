/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 08:16:00 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/04/29 11:38: by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
# define FT_MD5_H

# include <stddef.h>

# include "ft_ssl.h"
# include "structs.h"
# include "ftstream.h"

# define MD5_CHUNK_SIZE 64

# define MD5_END_BIT 0x80

# define SET_CHUNK_BIT(c) (c->msg[c->size] = MD5_END_BIT)

extern unsigned int				g_s[64];
extern unsigned int				g_k[64];
extern const t_md5_step_helper	g_md5_step_dispatch_table[];

# define GET_STEP_FUNC(i) (g_md5_step_dispatch_table[i / 16])

void							md5_first_step(t_md5_digest digest,
	unsigned int *f, unsigned int *g, int i);
void							md5_second_step(t_md5_digest digest,
	unsigned int *f, unsigned int *g, int i);
void							md5_third_step(t_md5_digest digest,
	unsigned int *f, unsigned int *g, int i);
void							md5_forth_step(t_md5_digest digest,
	unsigned int *f, unsigned int *g, int i);

t_digest						md5_init_digest(void);

t_digest						md5(t_stream stream, t_print_digest *cb);
void							md5_hash(unsigned char *chunk,
	t_md5_digest *digest);
int								md5_rocess_chunk(t_chunk *chunk,
	t_md5_digest *d, size_t *total);


#endif
