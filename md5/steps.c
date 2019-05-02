/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   steps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 21:40:14 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/05/02 10:25:21 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_md5.h"

void							md5_first_step(t_md5_digest digest,
	unsigned int *f, unsigned int *g, int i)
{
	*f = (digest.b & digest.c) | ((~digest.b) & digest.d);
	*g = i;
}

void							md5_second_step(t_md5_digest digest,
	unsigned int *f, unsigned int *g, int i)
{
	*f = (digest.d & digest.b) | ((~digest.d) & digest.c);
	*g = (5 * i + 1) % 16;
}

void							md5_third_step(t_md5_digest digest,
	unsigned int *f, unsigned int *g, int i)
{
	*f = digest.b ^ digest.c ^ digest.d;
	*g = (3 * i + 5) % 16;
}

void							md5_forth_step(t_md5_digest digest,
	unsigned int *f, unsigned int *g, int i)
{
	*f = digest.c ^ (digest.b | (~digest.d));
	*g = (7 * i) % 16;
}
