/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 12:38:07 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/05/02 12:34:36 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "ft_md5.h"

# include <stddef.h>
# include <sys/types.h>

# include "structs.h"
# include "ftstream.h"

# define ALG_NUM 1
# define PREFIX "ft_ssl:"
# define USAGE "usage: ft_ssl command [command opts] [command args]"

extern int						g_printed_file;
extern int						g_printed_stdin;
extern int						g_printed_string;

enum	e_err
{
	ERR_READ_FILE,
	ERR_FILE_NOT_FOUND,
	ERR_ILLEGAL_OPTION,
	ERR_NO_ARG,
};
typedef enum e_err		t_err;

extern char				*g_hash_func_name;

void					error_handler(t_err errcode,
	int exit, const char *info);

/*
**	Flags
*/

# define FLAG_P 1
# define FLAG_R 2
# define FLAG_Q 4
# define FLAG_S 8
# define MD5_FLAGS "prqs"

char					*ssl_parse_flag(char *arg);
int						ssl_get_toggle_flag(int get, int toggle);

# define GET_FLAG(f) (ssl_get_toggle_flag(f, 0))
# define DOIFTRUE(cond, expr) ((cond) ? (expr) : (void)0)
# define UNSET_FLAG(f) (DOIFTRUE(GET_FLAG(f), ssl_get_toggle_flag(0, f)))

void					print_chunk(t_chunk chunk);
t_chunk					*get_chunk(int fd, size_t chunk_size);
void					padd_chunk(t_chunk *chunk, size_t total);
ssize_t					read_chunk(int fd, size_t size, void **buf);
t_chunk					*get_chunk_stream(t_stream stream, size_t size);
t_chunk					*get_chunk_string(t_stream stream, size_t size);

void					ssl_print_digest(t_digest d, t_stream s);

#endif
