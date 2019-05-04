/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 05:28:31 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/05/04 14:35:11 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ftstream.h"

#include "memory.h"
#include "numbers.h"

#include <stdlib.h>
#include <unistd.h>

static t_chunk			*init_chunk(size_t size)
{
	t_chunk		*ret;

	ret = malloc(sizeof(t_chunk));
	ret->msg = malloc(size);
	ft_bzero(ret->msg, size);
	ret->max_size = size;
	return (ret);
}

static t_chunk			*get_chunk(int fd, size_t chunk_size)
{
	size_t			ret;
	t_chunk			*chunk;

	chunk = init_chunk(chunk_size);
	ret = read(fd, chunk->msg, chunk->max_size);
	chunk->size = ret;
	if (ret < 0)
	{
		ft_free(2, chunk->msg, chunk);
		return (NULL);
	}
	return (chunk);
}

int						prepare_chunk(t_chunk *chunk,
	size_t total, int *eos, int is_big_endian)
{
	int		last;

	last = 0;
	if (chunk->size < chunk->max_size)
	{
		*eos += chunk->size < chunk->max_size;
		last = chunk->size <= chunk->max_size - 8;
		total = is_big_endian ? to_le_64(total * 8) : total * 8;
		if (*eos == 1)
			SET_CHUNK_BIT(chunk);
		if (last)
			ft_memcpy((chunk->msg + chunk->max_size - 8),
				&total, sizeof(size_t));
	}
	return (last);
}

t_chunk					*get_chunk_stream(t_stream stream,
	size_t chunk_size)
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

t_chunk					*get_chunk_string(t_stream stream,
	size_t chunk_size)
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
