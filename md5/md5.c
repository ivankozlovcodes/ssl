/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 21:06:16 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/05/02 10:55:26 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_md5.h"

#include "memory.h"
#include "numbers.h"
#include "ft_printf.h"

/*
void	md5_stdin(void)
{
	t_md5			md5;

	md5.d = g_printed_stdin ? md5_init_digest_empty_string() : init_digest();
	md5.message = ssl_get_toggle_flag(FLAG_P, 0)
		? string_init(MD5_CHUNK_SIZE) : NULL;
	md5_fd(0 - g_printed_stdin, &md5);
	md5_print_result(NULL, md5);
	if (md5.message)
		string_destroy(md5.message, FALSE);
	g_printed_stdin = 1;
}
*/

void	md5_hash(unsigned char *chunk, t_md5_digest *digest)
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

int		md5_process_chunk(t_chunk *chunk, t_md5_digest *d, size_t *total)
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
		// print_chunk(*chunk);
	}
	// ft_printf("%.8x %.8x %.8x %.8x\n", d->a, d->b, d->c, d->d);
	md5_hash(chunk->msg, d);
	// ft_printf("%.8x %.8x %.8x %.8x\n", d->a, d->b, d->c, d->d);
	return (last);
}

t_digest	md5(t_stream stream, t_print_digest *cb)
{
	t_digest	d;
	t_md5		md5;
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
		// free chunk
	}
	if (cb)
		(*cb)(d, stream);
	return (d);
}
