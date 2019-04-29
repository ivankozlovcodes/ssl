/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 11:23:09 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/04/29 11:30:16 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_md5.h"

#include "memory.h"
#include "ftstring.h"

int			g_printed_string = 0;

void	md5_string(char *string)
{
	t_md5				md5;
	size_t				pos;
	size_t				total;
	t_chunk				chunk;
	const size_t		s_len = ft_strlen((const char *)string);

	pos = 0;
	total = 0;
	md5.d = init_digest();
	md5.message = NULL;
	while (pos <= s_len)
	{
		chunk.msg = ft_memdup(string + pos, MD5_CHUNK_SIZE);
		pos += MD5_CHUNK_SIZE;
		chunk.size = pos > s_len ? s_len % MD5_CHUNK_SIZE : MD5_CHUNK_SIZE;
		ft_bzero(chunk.msg + chunk.size, MD5_CHUNK_SIZE - chunk.size);
		md5_process_chunk(&chunk, &(md5.d), &total);
	}
	md5_print_result(string, md5);
	g_printed_string = 1;
}
