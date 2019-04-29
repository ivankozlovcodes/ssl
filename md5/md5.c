/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 21:06:16 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/04/29 12:30:42 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_md5.h"

#include "memory.h"
#include "numbers.h"
#include "ft_printf.h"

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

void	md5_print_result(const char *filename, t_md5 md5)
{
	char			quote;
	unsigned int	*digest;

	quote = ssl_get_toggle_flag(FLAG_S, 0) ? '"' : 0;
	if (filename && !ssl_get_toggle_flag(FLAG_Q | FLAG_R, 0))
		ft_printf("MD5 (%c%s%c) = ", quote, filename, quote);
	if (ssl_get_toggle_flag(FLAG_P, 0) && md5.message)
		ft_printf("%s", md5.message->content);
	digest = digest_to_array(md5.d);
	ft_printf("%.8x%.8x%.8x%.8x", digest[0], digest[1], digest[2], digest[3]);
	if (filename && ssl_get_toggle_flag(FLAG_R, 0) && !ssl_get_toggle_flag(FLAG_Q, 0))
		ft_printf(" %c%s%c", quote, filename, quote);
	ft_printf("\n");
}

void	md5_main(int ac, char *av[])
{
	int				i;
	char			*flag_leftover;

	i = -1;
	while (++i < ac)
	{
		if (av[i][0] == '-' && !g_printed_file)
		{
			flag_leftover = ssl_parse_flag(av[i]);
			if (ssl_get_set_flag(FLAG_P, 0))
				md5_stdin();
			if (*flag_leftover)
				md5_string(flag_leftover);
			ssl_get_set_flag(0, 0);
			continue ;
		}
		ssl_get_set_flag(FLAG_S, 0) ? md5_string(av[i]) : md5_file(av[i]);
		ssl_get_set_flag(0, 0);
	}
	if (!g_printed_file && !g_printed_string)
	{
		if (ssl_get_set_flag(FLAG_S, 0))
			error_handler(ERR_NO_ARG, 1, "s");
		md5_stdin();
	}
}
