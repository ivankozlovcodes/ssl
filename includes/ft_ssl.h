/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 12:38:07 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/04/27 23:30:21 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stddef.h>
# include <sys/types.h>

# include "structs.h"

# define ALG_NUM 1
# define USAGE "usage: ft_ssl command [command opts] [command args]"

enum	e_err
{
	ERR_READ_FILE,
	ERR_FILE_NOT_FOUND,
	ERR_ILLEGAL_OPTION,
};

typedef enum e_err		t_err;

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
int						ssl_get_set_flag(int get, int set);

ssize_t					read_chunk(int fd, size_t size, void **buf);
t_chunk					*get_chunk(int fd, size_t chunk_size);

typedef void			(*t_hash_main)(int, char*[]);

#endif
