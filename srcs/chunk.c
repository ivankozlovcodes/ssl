/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 05:28:31 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/05/02 12:37:47 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "structs.h"
#include "ftstream.h"

#include "ft_printf.h"
#include "memory.h"

#include <stdlib.h>
#include <unistd.h>

void			padd_chunk(t_chunk *chunk, size_t total)
{
	total = total * 8;
	ft_memcpy((chunk->msg + 56), &total, sizeof(size_t));
}

t_chunk			*init_chunk(size_t size)
{
	t_chunk		*ret;

	ret = malloc(sizeof(t_chunk));
	ret->msg = malloc(size);
	return (ret);
}

t_chunk			*get_chunk(int fd, size_t chunk_size)
{
	ssize_t			read;
	t_chunk			*ret;

	ret = init_chunk(chunk_size);
	read = read_chunk(fd, chunk_size, (void **)&ret->msg);
	ret->size = read;
	if (read < 0)
	{
		ft_free(2, ret->msg, ret);
		return (NULL);
	}
	return (ret);
}

t_chunk			*get_chunk_stream(t_stream stream, size_t chunk_size)
{
	t_chunk		*chunk;

	if (stream.fd >= 0)
		chunk = get_chunk(stream.fd, chunk_size);
	else
		chunk = get_chunk_string(stream, chunk_size);
	if (stream.content)
		string_append(stream.content, (char *)chunk->msg);
	return (chunk);
}

t_chunk			*get_chunk_string(t_stream stream, size_t chunk_size)
{
	t_chunk			*chunk;

	chunk = init_chunk(chunk_size);
	if (stream.pos <= stream.size)
	{
		ft_memcpy(chunk->msg, stream.string + stream.pos, chunk_size);
		stream.pos += chunk_size;
		chunk->size = stream.pos > stream.size
			? stream.size % chunk_size : chunk_size;
		ft_bzero(chunk->msg + chunk->size, chunk_size - chunk->size);
	}
	return (chunk);
}
