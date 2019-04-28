/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 20:32:24 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/04/27 23:41:07 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_md5.h"

#include "ft_math.h"
#include "strings.h"

int				ssl_get_set_flag(int get, int set)
{
	static unsigned char	flags;

	flags |= set;
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
		flag = ft_pow(2, idx);
		ssl_get_set_flag(0, flag);
		arg++;
	}
}

int				ssl_parse_flags(int ac, char *av[])
{
	int		i;

	i = -1;
	while (++i < ac - 1)
	{
		if (*av[i] != '-')
			break ;
		ssl_parse_flag(*av + 1);
	}
	return (i);
}
