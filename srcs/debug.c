/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 05:20:21 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/05/04 05:21:51 by ivankozlov       ###   ########.fr       */
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
