/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 05:20:21 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/05/04 12:05:46 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "ft_printf.h"

void					print_chunk(t_chunk chunk)
{
	size_t		i;

	i = -1;
	while (++i < chunk.max_size)
		ft_printf("%.2x%s", chunk.msg[i], i % 8 == 7 ? " " : "");
	ft_printf("\n");
}

unsigned int			*digest_to_array(t_digest digest)
{
	size_t			i;
	unsigned int	*ret;

	i = -1;
	while (++i < digest.size)
		ret[i] = digest.words[i];
	return (ret);
}
