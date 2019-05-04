/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 06:04:36 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/05/04 10:59:20 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_md5.h"

#include "memory.h"
#include "numbers.h"

t_digest	md5_init_digest(void)
{
	static const unsigned int	defaults[] = { 0x67452301, 0xefcdab89,
		0x98badcfe, 0x10325476 };
	t_digest					digest;

	digest.size = 4;
	digest.words = ft_memdup(defaults, sizeof(unsigned int) * 4);
	return (digest);
}

void		md5(unsigned char *chunk, t_digest digest)
{
	int					i;
	unsigned int		g;
	unsigned int		f;
	unsigned int		*m;
	unsigned int		*tmp;

	i = -1;
	tmp = ft_memdup(digest.words, sizeof(unsigned int) * digest.size);
	m = (unsigned int *)chunk;
	while (++i < 64)
	{
		(GET_STEP_FUNC(i))(tmp, &f, &g, i);
		f += tmp[0] + g_k[i] + m[g];
		tmp[0] = tmp[3];
		tmp[3] = tmp[2];
		tmp[2] = tmp[1];
		tmp[1] += left_rotate(f, g_s[i]);
	}
	digest.words[0] += tmp[0];
	digest.words[1] += tmp[1];
	digest.words[2] += tmp[2];
	digest.words[3] += tmp[3];
	ft_free(1, tmp);
}
