/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 10:32:16 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/05/02 11:08:55 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ftstream.h"

#include "ftstring.h"

#include <fcntl.h>

int					g_printed_file = 0;
int					g_printed_stdin = 0;
int					g_printed_string = 0;

t_stream			build_stream_fd(char *filename)
{
	t_stream		s;

	s.fd = filename ? open(filename, O_RDONLY) : 0;
	s.string = NULL;
	s.filename = filename;
	s.content = s.fd == 0 ? string_init(0x4000) : NULL;
	if (s.fd < 0)
		error_handler(ERR_FILE_NOT_FOUND, 0, filename);
	g_printed_file = g_printed_file || filename;
	g_printed_stdin = g_printed_file || !filename;
	return (s);
}

t_stream			build_stream_string(char *string)
{
	t_stream		s;

	s.fd = -1;
	s.content = NULL;
	s.filename = NULL;
	s.string = string;
	s.size = ft_strlen(string);
	g_printed_string = 1;
	return (s);
}
