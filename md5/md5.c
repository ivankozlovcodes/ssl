/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 21:06:16 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/05/02 12:38:18 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_md5.h"

#include "memory.h"
#include "numbers.h"
#include "ft_printf.h"

void		md5_hash(unsigned char *chunk, t_md5_digest *digest)
{
	int					i;
	unsigned int		g;
	unsigned int		f;
	unsigned int		*m;
	t_md5_digest		tmp;

	i = -1;
	tmp = *digest;
	m = (unsigned int *)chunk;
	while (++i < 64)
	{
		(GET_STEP_FUNC(i))(tmp, &f, &g, i);
		f += tmp.a + g_k[i] + m[g];
		tmp.a = tmp.d;
		tmp.d = tmp.c;
		tmp.c = tmp.b;
		tmp.b += left_rotate(f, g_s[i]);
	}
	digest->a += tmp.a;
	digest->b += tmp.b;
	digest->c += tmp.c;
	digest->d += tmp.d;
}

int			md5_process_chunk(t_chunk *chunk, t_md5_digest *d, size_t *total)
{
	int			last;

	last = 0;
	*total = *total + chunk->size;
	if (chunk->size < MD5_CHUNK_SIZE)
	{
		SET_CHUNK_BIT(chunk);
		last = chunk->size < 56;
		if (last)
			padd_chunk(chunk, *total);
	}
	md5_hash(chunk->msg, d);
	return (last);
}

t_digest	md5(t_stream stream, t_print_digest *cb)
{
	t_digest	d;
	int			last;
	size_t		total;
	t_chunk		*chunk;

	last = 0;
	total = 0;
	if (stream.fd < 0 && !stream.string)
		return (d);
	d = md5_init_digest();
	while (!last)
	{
		chunk = get_chunk_stream(stream, MD5_CHUNK_SIZE);
		last = md5_process_chunk(chunk, (t_md5_digest *)d.words, &total);
		ft_free(2, chunk->msg, chunk);
	}
	if (cb)
		(*cb)(d, stream);
	DOIFTRUE(stream.content, string_destroy(stream.content, FALSE));
	return (d);
}
