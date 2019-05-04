/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 13:26:27 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/05/04 13:28:19 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha256.h"

#include "memory.h"

t_digest		sha224_init_digest(void)
{
	t_digest						d;
	static const unsigned int		defaults[] = {
		0xc1059ed8, 0x367cd507, 0x3070dd17, 0xf70e5939,
		0xffc00b31, 0x68581511, 0x64f98fa7, 0xbefa4fa4 };

	d.size = 8;
	d.words = ft_memdup(defaults, sizeof(int) * 8);
	return (d);
}
