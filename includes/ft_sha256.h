/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 06:11:23 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/05/04 13:27:35 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHA256_H
# define FT_SHA256_H

# include "structs.h"

# define E0 0
# define E1 1
# define MA 2
# define CH 3
# define T1 4
# define T2 5

# define CALC_E0(a) (rotr(a, 2) ^ rotr(a, 13) ^ rotr(a, 22))
# define CALC_MA(a, b, c) ((a & b) ^ (a & c) ^ (b & c))
# define CALC_E1(e) (rotr(e, 6) ^ rotr(e, 11) ^ rotr(e, 25))
# define CALC_CH(e, f, g) ((e & f) ^ (~e & g))

extern unsigned int				g_sha256_k[64];

t_digest	sha256_init_digest(void);
void		sha256(unsigned char *chunk, t_digest digest);


t_digest	sha224_init_digest(void);

/*
**	Stands for AlphabetIndex.
**	Gets value of array arr at position of
**	index ch in the english lowercase alphabet.
**	Respects ASCII codes.
**	todo: move to libft
*/
# define AI(arr, ch) ((arr)[(ch) - 'a'])

#endif
