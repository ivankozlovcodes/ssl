/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 07:55:36 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/05/02 12:37:22 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ftstring.h"
#include "ft_printf.h"

#include "memory.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

char			*g_hash_func_name = NULL;

t_hash_func		*get_hash_func(char *name)
{
	int							idx;
	static char const			*lookup[ALG_NUM + 1] = { "md5", NULL };
	static t_hash_func			funcs[] = { &md5 };

	g_hash_func_name = name;
	idx = ft_straridx(name, (char **)lookup);
	return (idx == -1 ? NULL : &funcs[idx]);
}

void			hash_main(int ac, char *av[], t_hash_func func)
{
	int								i;
	char							*flag_leftover;
	static t_print_digest			cb = ssl_print_digest;

	i = -1;
	while (++i < ac)
	{
		if (av[i][0] == '-' && !g_printed_file)
		{
			flag_leftover = ssl_parse_flag(av[i]);
			if (ssl_get_toggle_flag(FLAG_P, 0))
				func(build_stream_fd(NULL), &cb);
			if (*flag_leftover && ssl_get_toggle_flag(FLAG_S, 0)
				&& !ssl_get_toggle_flag(0, FLAG_S))
				func(build_stream_string(flag_leftover), &cb);
			UNSET_FLAG(FLAG_P);
			continue ;
		}
		ssl_get_toggle_flag(FLAG_S, 0) ? func(build_stream_string(av[i]), &cb)
			: func(build_stream_fd(av[i]), &cb);
		UNSET_FLAG(FLAG_S);
	}
	DOIFTRUE(ssl_get_toggle_flag(FLAG_S, 0), error_handler(ERR_NO_ARG, 1, "s"));
	if (!g_printed_file && !g_printed_string && !g_printed_stdin)
		func(build_stream_fd(NULL), &cb);
}

int				main(int ac, char *av[])
{
	t_hash_func		*func;
	char			*algorithm;

	if (ac < 2)
	{
		ft_printf("%s\n", USAGE);
		return (-1);
	}
	algorithm = av[1];
	func = get_hash_func(algorithm);
	if (!func)
	{
		ft_printf("Error: %s is invalid command.\n", algorithm);
		return (-1);
	}
	hash_main(ac - 2, av + 2, *func);
	return (0);
}
