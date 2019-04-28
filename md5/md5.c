/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 21:06:16 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/04/28 00:39:20 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "ft_ssl.h"
#include "ft_md5.h"
#include "memory.h"
#include "numbers.h"

void	md5(unsigned char *chunk, t_md5_digest *digest)
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
			md5_padd_chunk(chunk, *total);
	}
	md5(chunk->msg, d);
	return (last);
}

void	md5_file(const char *filename)
{
	t_md5_digest	d;
	int				fd;
	int				last;
	size_t			total;
	t_chunk			*chunk;

	d = init_digest();
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (error_handler(ERR_FILE_NOT_FOUND, 0, filename));
	last = 0;
	total = 0;
	while ((chunk = get_chunk(fd, MD5_CHUNK_SIZE)) && !last)
	{
		last = md5_process_chunk(chunk, &d, &total);
		ft_free(2, chunk->msg, chunk);
	}
	print_digest(d);
	close(fd);
}

void	md5_main(int ac, char *av[])
{
	int				i;

	i = 0;
	while (i < ac)
	{
		ssl_get_set_flag(0, 0);
		i += ssl_parse_flags(ac - i, av + i);
		md5_file(av[i]);
		i++;
	}
}
