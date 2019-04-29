/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 11:12:58 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/04/29 12:32:03 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "ft_ssl.h"
#include "ft_md5.h"

#include "memory.h"

int		g_printed_file = 0;

void	md5_fd(const int fd, t_md5 *md5)
{
	int				last;
	size_t			total;
	t_chunk			*chunk;

	last = 0;
	total = 0;
	while (!last && (chunk = get_chunk(fd, MD5_CHUNK_SIZE)))
	{
		if (md5->message)
			string_append(md5->message, (char *)chunk->msg);
		last = md5_process_chunk(chunk, &(md5->d), &total);
		ft_free(2, chunk->msg, chunk);
	}
}

void	md5_stdin(void)
{
	t_md5			md5;
	static int		printed = 0;

	md5.d = printed ? init_digest_empty_string() : init_digest();
	md5.message = ssl_get_set_flag(FLAG_P, 0)
		? string_init(MD5_CHUNK_SIZE) : NULL;
	md5_fd(0 - printed, &md5);
	md5_print_result(NULL, md5);
	if (md5.message)
		string_destroy(md5.message, FALSE);
	printed = 1;
}

void	md5_file(const char *filename)
{
	int				fd;
	t_md5			md5;

	md5.d = init_digest();
	md5.message = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_handler(ERR_FILE_NOT_FOUND, 0, filename));
	md5_fd(fd, &md5);
	md5_print_result(filename, md5);
	g_printed_file = 1;
	close(fd);
}
