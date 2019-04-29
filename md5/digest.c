/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 11:33:55 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/04/29 11:34:29 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "memory.h"
#include "structs.h"
#include "numbers.h"
#include "ft_printf.h"

t_md5_digest	init_digest(void)
{
	static const unsigned int	defaults[] = { 0x67452301, 0xefcdab89,
		0x98badcfe, 0x10325476 };

	return (*(t_md5_digest *)defaults);
}

t_md5_digest	init_digest_empty_string(void)
{
	static const unsigned int	defaults[] = { 0xd98c1dd4, 0x04b2008f,
		0x980980e9, 0x7e42f8ec };

	return (*(t_md5_digest *)defaults);
}

unsigned int	*digest_to_array(t_md5_digest d)
{
	const unsigned int	ret[4] = { to_little_endian(d.a), to_little_endian(d.b),
		to_little_endian(d.c), to_little_endian(d.d) };

	return (ft_memdup(ret, sizeof(unsigned int) * 4));
}

void			print_digest(t_md5_digest d)
{
	int					i;
	unsigned int		*arr;

	i = -1;
	arr = digest_to_array(d);
	while (++i < 4)
		ft_printf("%.8x ", arr[i]);
	ft_printf("\n");
}
