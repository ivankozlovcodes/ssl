/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 12:38:07 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/04/29 16:40:19 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stddef.h>
# include <sys/types.h>

# include "structs.h"

# define ALG_NUM 1
# define PREFIX "ft_ssl:"
# define USAGE "usage: ft_ssl command [command opts] [command args]"

# define DOIFTRUE(cond, expr) ((cond) ? (expr) : (void)0)

enum	e_err
{
	ERR_READ_FILE,
	ERR_FILE_NOT_FOUND,
	ERR_ILLEGAL_OPTION,
	ERR_NO_ARG,
};

extern char				*g_hash_func_name;

void					error_handler(t_err errcode,
	int exit, const char *info);

/*
**	MD5
*/
void					md5_main(int ac, char *av[]);

/*
**	Flags
*/
int						ssl_parse_flags(int ac, char *av[]);
int						ssl_get_toggle_flag(int get, int toggle);

# define GET_FLAG(f) (ssl_get_toggle_flag(f, 0))
# define UNSET_FLAG(f) (DOIFTRUE(GET_FLAG(f), ssl_get_toggle_flag(0, f)))

ssize_t					read_chunk(int fd, size_t size, void **buf);
t_chunk					*get_chunk(int fd, size_t chunk_size);

typedef void			(*t_hash_main)(int, char*[]);

#endif
