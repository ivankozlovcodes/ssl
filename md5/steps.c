/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 21:40:14 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/05/04 05:48:10 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_md5.h"

void							md5_first_step(unsigned int *digest,
	unsigned int *f, unsigned int *g, int i)
{
	*f = (digest[1] & digest[2]) | ((~digest[1]) & digest[3]);
	*g = i;
}

void							md5_second_step(unsigned int *digest,
	unsigned int *f, unsigned int *g, int i)
{
	*f = (digest[3] & digest[1]) | ((~digest[3]) & digest[2]);
	*g = (5 * i + 1) % 16;
}

void							md5_third_step(unsigned int *digest,
	unsigned int *f, unsigned int *g, int i)
{
	*f = digest[1] ^ digest[2] ^ digest[3];
	*g = (3 * i + 5) % 16;
}

void							md5_forth_step(unsigned int *digest,
	unsigned int *f, unsigned int *g, int i)
{
	*f = digest[2] ^ (digest[1] | (~digest[3]));
	*g = (7 * i) % 16;
}
