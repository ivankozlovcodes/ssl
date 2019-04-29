/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 20:32:24 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/04/29 16:07:10 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_md5.h"

#include "ftstring.h"
#include "ft_printf.h"

int			ssl_get_toggle_flag(int get, int toggle)
{
	static unsigned char	flags;

	flags ^= toggle;
	return (flags & get);
}

char		*ssl_parse_flag(char *arg)
{
	int		i;
	int		idx;
	int		flag;

	i = 0;
	while (arg[++i])
	{
		idx = ft_strchri(MD5_FLAGS, arg[i]);
		if (idx == -1)
			error_handler(ERR_ILLEGAL_OPTION, 1, &(arg[i]));
		flag = 1 << idx;
		ssl_get_toggle_flag(0, flag);
		if (flag == FLAG_S)
			return (arg + i + 1);
	}
	return (arg + i);
}
