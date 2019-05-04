/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 08:16:00 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/05/04 06:28:25 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
# define FT_MD5_H

# include <stddef.h>

# include "structs.h"
# include "ftstream.h"

extern unsigned int				g_s[64];
extern unsigned int				g_k[64];
extern const t_md5_step_helper	g_md5_step_dispatch_table[];

# define GET_STEP_FUNC(i) (g_md5_step_dispatch_table[i / 16])

void							md5_first_step(unsigned int *digest,
	unsigned int *f, unsigned int *g, int i);
void							md5_second_step(unsigned int *digest,
	unsigned int *f, unsigned int *g, int i);
void							md5_third_step(unsigned int *digest,
	unsigned int *f, unsigned int *g, int i);
void							md5_forth_step(unsigned int *digest,
	unsigned int *f, unsigned int *g, int i);

t_digest						md5_init_digest(void);
void							md5(unsigned char *chunk, t_digest digest);

#endif
