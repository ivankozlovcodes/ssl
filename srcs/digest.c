/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 11:33:55 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/05/02 11:14:35 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

#include "memory.h"
#include "numbers.h"
#include "ft_printf.h"

t_digest		md5_init_digest(void)
{
	static const unsigned int	defaults[] = { 0x67452301, 0xefcdab89,
		0x98badcfe, 0x10325476 };
	t_digest					digest;

	digest.size = 4;
	digest.words = ft_memdup(defaults, sizeof(unsigned int) * 4);
	return (digest);
}

t_md5_digest	md5_init_digest_empty_string(void)
{
	static const unsigned int	defaults[] = { 0xd98c1dd4, 0x04b2008f,
		0x980980e9, 0x7e42f8ec };

	return (*(t_md5_digest *)defaults);
}

void			ssl_print_digest(t_digest d, t_stream s)
{
	size_t			i;
	char			*quote;
	char			*input_name;

	input_name = s.filename ? s.filename : s.string;
	quote = s.string ? "\"" : "";
	if (input_name && !ssl_get_toggle_flag(FLAG_Q | FLAG_R, 0))
		ft_printf("MD5 (%s%s%s) = ", quote, input_name, quote);
	if (ssl_get_toggle_flag(FLAG_P, 0) && s.content)
		ft_printf("%s", s.content->content);
	i = -1;
	while (++i < d.size)
		ft_printf("%.8x", to_little_endian(d.words[i]));
	if (input_name && ssl_get_toggle_flag(FLAG_R, 0)
		&& !ssl_get_toggle_flag(FLAG_Q, 0))
		ft_printf(" %s%s%s", quote, input_name, quote);
	ft_printf("\n");
}
