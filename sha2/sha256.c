/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 06:04:17 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/05/04 15:06:54 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha256.h"

#include "memory.h"
#include "numbers.h"

t_digest		sha256_init_digest(void)
{
	t_digest						d;
	static const unsigned int		defaults[] = {
		0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A,
		0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19 };

	d.size = 8;
	d.words = ft_memdup(defaults, sizeof(int) * 8);
	return (d);
}

unsigned int	*init_w(unsigned char *chunk)
{
	int					i;
	size_t				s0;
	size_t				s1;
	unsigned int		*w;

	w = ft_memalloc(sizeof(unsigned int) * 64);
	ft_memcpy(w, (unsigned int *)chunk, sizeof(unsigned int) * 16);
	i = -1;
	while (++i < 16)
		w[i] = to_little_endian(w[i]);
	i = 15;
	while (++i < 64)
	{
		s0 = rotr(w[i - 15], 7) ^ rotr(w[i - 15], 18) ^ (w[i - 15] >> 3);
		s1 = rotr(w[i - 2], 17) ^ rotr(w[i - 2], 19) ^ (w[i - 2] >> 10);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
	}
	return (w);
}

void			update_help(unsigned int *tmp,
	unsigned int help[], unsigned int *w, int i)
{
	help[E0] = CALC_E0(AI(tmp, 'a'));
	help[MA] = CALC_MA(AI(tmp, 'a'), AI(tmp, 'b'), AI(tmp, 'c'));
	help[T2] = help[E0] + help[MA];
	help[E1] = CALC_E1(AI(tmp, 'e'));
	help[CH] = CALC_CH(AI(tmp, 'e'), AI(tmp, 'f'), AI(tmp, 'g'));
	help[T1] = AI(tmp, 'h') + help[E1] + help[CH] + g_sha256_k[i] + w[i];
}

void			update_tmp_digest(unsigned int *tmp, unsigned int help[])
{
	AI(tmp, 'h') = AI(tmp, 'g');
	AI(tmp, 'g') = AI(tmp, 'f');
	AI(tmp, 'f') = AI(tmp, 'e');
	AI(tmp, 'e') = AI(tmp, 'd') + help[T1];
	AI(tmp, 'd') = AI(tmp, 'c');
	AI(tmp, 'c') = AI(tmp, 'b');
	AI(tmp, 'b') = AI(tmp, 'a');
	AI(tmp, 'a') = help[T1] + help[T2];
}

void			sha256(unsigned char *chunk, t_digest digest)
{
	size_t			i;
	unsigned int	*w;
	unsigned int	*tmp;
	unsigned int	help[6];

	i = -1;
	w = init_w(chunk);
	tmp = ft_memdup(digest.words, sizeof(unsigned int) * digest.size);
	while (++i < 64)
	{
		update_help(tmp, help, w, i);
		update_tmp_digest(tmp, help);
	}
	i = -1;
	while (++i < digest.size)
		digest.words[i] += tmp[i];
	ft_free(2, w, tmp);
}
