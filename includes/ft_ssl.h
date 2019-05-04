/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 12:38:07 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/05/04 05:53:00 by ivankozlov       ###   ########.fr       */
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
# define COMMANDS_MSG "Avaliable commands are:\nmd5"

# define END_BIT 0x80
# define MESSAGE_LEN_BYTES 8

# define SET_CHUNK_BIT(c) (c->msg[c->size] = END_BIT)

extern int						g_printed_file;
extern int						g_printed_stdin;
extern int						g_printed_string;

enum	e_err
{
	ERR_NO_ARG,
	ERR_READ_FILE,
	ERR_NO_COMMAND,
	ERR_ILLEGAL_OPTION,
	ERR_FILE_NOT_FOUND,
	ERR_INVALID_COMMAND,
};
typedef enum e_err				t_err;

extern char						*g_hash_func_name;

void							error_handler(t_err errcode,
	int exit, const char *info);

struct							s_ssl_main
{
	size_t						chunk_size;

	t_hash_chunk				hash;
	t_init_digest				init_digest;
};
typedef struct s_ssl_main		t_ssl_main;

/*
**	Flags
*/

# define FLAG_P 1
# define FLAG_R 2
# define FLAG_Q 4
# define FLAG_S 8
# define MD5_FLAGS "prqs"

char							*ssl_parse_flag(char *arg);
int								ssl_get_toggle_flag(int get, int toggle);

# define GET_FLAG(f) (ssl_get_toggle_flag(f, 0))
# define DOIFTRUE(cond, expr) ((cond) ? (expr) : (void)0)
# define UNSET_FLAG(f) (DOIFTRUE(GET_FLAG(f), ssl_get_toggle_flag(0, f)))

/*
**	Chunk
*/

int								prepare_chunk(t_chunk *chunk, size_t *total);
t_chunk							*get_chunk_string(t_stream stream, size_t size);
t_chunk							*get_chunk_stream(t_stream stream, size_t size);

t_digest						hash_stream(t_stream stream,
	t_ssl_main main, t_print_digest *cb);

void							ssl_print_digest(t_digest d, t_stream s);

/*
**	Debug
*/

void							print_chunk(t_chunk chunk);

#endif
