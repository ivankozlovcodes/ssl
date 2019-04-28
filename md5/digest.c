/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 17:02:57 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/04/28 00:35:33 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include "structs.h"
#include "numbers.h"
#include "ft_printf.h"

t_md5_digest	init_digest()
{
	static const unsigned int	defaults[] =
		{ 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476 };
	return *(t_md5_digest *)defaults;
}

unsigned int	*digest_to_array(t_md5_digest d)
{
	unsigned int	ret[4];

	ret[0] = to_little_endian(d.a);
	ret[1] = to_little_endian(d.b);
	ret[2] = to_little_endian(d.c);
	ret[3] = to_little_endian(d.d);
	return (ft_memdup(ret, sizeof(unsigned int) * 4));
}

void			print_digest(t_md5_digest d)
{
	int					i;
	unsigned int		*arr;

	i = -1;
	arr = digest_to_array(d);
	while (++i < 4)
		ft_printf("%.8x", arr[i]);
	ft_printf("\n");
}
