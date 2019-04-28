/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 08:16:00 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/04/28 00:34:11 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
# define FT_MD5_H

# include <stddef.h>
# include "structs.h"

# define MD5_FLAGS "prqs"

# define MD5_CHUNK_SIZE 64

extern unsigned int		g_s[64];
extern unsigned int		g_k[64];

# define MD5_END_BIT 0x80

# define SET_CHUNK_BIT(c) (c->msg[c->size] = MD5_END_BIT)

/*
**	Step functions
*/
void							md5_first_step(t_md5_digest digest,
	unsigned int *f, unsigned int *g, int i);
void							md5_second_step(t_md5_digest digest,
	unsigned int *f, unsigned int *g, int i);
void							md5_third_step(t_md5_digest digest,
	unsigned int *f, unsigned int *g, int i);
void							md5_forth_step(t_md5_digest digest,
	unsigned int *f, unsigned int *g, int i);

extern const t_md5_step_helper		g_md5_step_dispatch_table[];

# define GET_STEP_FUNC(i) (g_md5_step_dispatch_table[i / 16])

t_md5_digest						init_digest();
void								md5(unsigned char *chunk,
	t_md5_digest *digest);
void			md5_padd_chunk(t_chunk *chunk, size_t total);
void			print_digest(t_md5_digest d);

// helpers
void	print_chunk(unsigned char *chunk);

#endif
