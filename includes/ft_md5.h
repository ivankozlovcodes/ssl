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
# include "structs.h"

# define MD5_FLAGS "prqs"

# define FLAG_P 1
# define FLAG_R 2
# define FLAG_Q 4
# define FLAG_S 8

# define MD5_CHUNK_SIZE 64

# define MD5_END_BIT 0x80

# define SET_CHUNK_BIT(c) (c->msg[c->size] = MD5_END_BIT)

extern unsigned int				g_s[64];
extern unsigned int				g_k[64];
extern int						g_printed_file;
extern int						g_printed_string;
extern const t_md5_step_helper	g_md5_step_dispatch_table[];

# define GET_STEP_FUNC(i) (g_md5_step_dispatch_table[i / 16])

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

t_md5_digest					init_digest();
t_md5_digest					init_digest_empty_string();
void							print_digest(t_md5_digest d);
unsigned int					*digest_to_array(t_md5_digest d);

char							*ssl_parse_flag(char *arg);

void							md5(unsigned char *chunk,
	t_md5_digest *digest);
void							md5_padd_chunk(t_chunk *chunk, size_t total);
int								md5_process_chunk(t_chunk *chunk,
	t_md5_digest *d, size_t *total);
void							md5_print_result(const char *filename,
	t_md5 md5);

void							md5_stdin(void);
void							md5_string(char *string);
void							md5_file(const char *filename);
void							md5_fd(const int fd, t_md5 *md5);

#endif
