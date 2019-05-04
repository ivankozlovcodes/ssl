/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 06:04:36 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/05/04 06:07:11 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_md5.h"

#include "memory.h"
#include "numbers.h"

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
