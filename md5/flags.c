/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 20:32:24 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/04/29 01:38:53 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_md5.h"

#include "ftstring.h"
#include "ft_printf.h"

int				ssl_get_set_flag(int get, int set)
{
	static unsigned char	flags;

	flags |= set;
	flags &= (get | set) > 0 ? flags : 0;
	return (flags & get);
}

static void		ssl_parse_flag(char *arg)
{
	int		idx;
	int		flag;

	while (*arg)
	{
		idx = ft_strchri(MD5_FLAGS, *arg);
		if (idx == -1)
			error_handler(ERR_ILLEGAL_OPTION, 1, &(*arg));
		flag = 1 << idx;
		ssl_get_set_flag(0, flag);
		arg++;
	}
}

int				ssl_parse_flags(int ac, char *av[])
{
	int		i;

	i = -1;
	while (++i < ac)
	{
		if (*av[i] != '-')
			break ;
		ssl_parse_flag(*(av + i) + 1);
	}
	return (i);
}
