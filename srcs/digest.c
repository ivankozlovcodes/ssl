/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 11:33:55 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/05/04 12:05:23 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_ssl.h"

#include "memory.h"
#include "numbers.h"
#include "ft_printf.h"

void			ssl_print_digest(t_ssl_main main,
	t_digest d, t_stream s)
{
	size_t			i;
	char			*quote;
	char			*input_name;

	input_name = s.filename ? s.filename : s.string;
	quote = s.string ? "\"" : "";
	if (input_name && !ssl_get_toggle_flag(FLAG_Q | FLAG_R, 0))
		ft_printf("%s (%s%s%s) = ", main.info.name, quote, input_name, quote);
	if (ssl_get_toggle_flag(FLAG_P, 0) && s.content)
		ft_printf("%s", s.content->content);
	i = -1;
	while (++i < d.size)
		ft_printf("%.8x", main.info.big_endian
			? d.words[i] : to_little_endian(d.words[i]));
	if (input_name && ssl_get_toggle_flag(FLAG_R, 0)
		&& !ssl_get_toggle_flag(FLAG_Q, 0))
		ft_printf(" %s%s%s", quote, input_name, quote);
	ft_printf("\n");
	ft_free(1, d.words);
}
