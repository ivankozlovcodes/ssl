/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chunk.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 14:07:21 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/04/29 09:57:00 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "ft_ssl.h"
#include "ft_md5.h"
#include "memory.h"

t_chunk			*init_chunk(size_t size)
{
	t_chunk		*ret;

	ret = malloc(sizeof(t_chunk));
	ret->msg = malloc(size);
	return (ret);
}

void			free_chunk(t_chunk *chunk)
{
	ft_free(2, chunk->msg, chunk);
}

void			md5_padd_chunk(t_chunk *chunk, size_t total)
{
	total = total * 8;
	ft_memcpy((chunk->msg + 56), &total, sizeof(size_t));
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
		free_chunk(ret);
		return (NULL);
	}
	return (ret);
}
