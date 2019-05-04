/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 07:55:36 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/05/04 13:50:18 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ftstring.h"

#include "memory.h"
#include "ftstring.h"

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

char			*g_hash_func_name = NULL;

void			init_ssl_main(char *algorithm, t_ssl_main *main)
{
	int							idx;
	char						*upper;
	static t_hash_chunk			hash_funcs[] = { &md5, &sha256, sha256 };
	static t_init_digest		digest_funcs[] = { &md5_init_digest,
		&sha256_init_digest, &sha224_init_digest };
	static t_algorithm_info		alg_info[] = {
		{ 64, 0, 4, "MD5" }, { 64, 1, 8, "SHA256" },
		{ 64, 1, 7, "SHA224" }, { 0, 0, 0, NULL }
	};

	idx = -1;
	upper = ft_strtoupper(ft_strdup(algorithm));
	while (alg_info[++idx].name)
		if (ft_strequ(upper, alg_info[idx].name))
		{
			g_hash_func_name = algorithm;
			main->info = alg_info[idx];
			main->hash = hash_funcs[idx];
			main->init_digest = digest_funcs[idx];
			break ;
		}
	ft_free(1, upper);
	if (alg_info[idx].name == NULL)
		error_handler(ERR_INVALID_COMMAND, 1, algorithm);
}

void			hash_main(int ac, char *av[], t_ssl_main m)
{
	int								i;
	char							*flag_leftover;
	static t_print_digest			cb = ssl_print_digest;

	i = -1;
	while (++i < ac)
	{
		if (av[i][0] == '-' && av[i][1] && !g_printed_file)
		{
			flag_leftover = ssl_parse_flag(av[i]);
			if (ssl_get_toggle_flag(FLAG_P, 0))
				hash_stream(stream_fd(NULL), m, &cb);
			if (*flag_leftover && ssl_get_toggle_flag(FLAG_S, 0)
				&& !ssl_get_toggle_flag(0, FLAG_S))
				hash_stream(stream_str(flag_leftover), m, &cb);
			UNSET_FLAG(FLAG_P);
			continue ;
		}
		ssl_get_toggle_flag(FLAG_S, 0) ? hash_stream(stream_str(av[i]), m, &cb)
			: hash_stream(stream_fd(av[i]), m, &cb);
		UNSET_FLAG(FLAG_S);
	}
	DOIFTRUE(ssl_get_toggle_flag(FLAG_S, 0), error_handler(ERR_NO_ARG, 1, "s"));
	if (!g_printed_file && !g_printed_string && !g_printed_stdin)
		hash_stream(stream_fd(NULL), m, &cb);
}

int				main(int ac, char *av[])
{
	t_ssl_main		main;
	char			*algorithm;

	if (ac < 2)
		error_handler(ERR_NO_COMMAND, 1, NULL);
	algorithm = av[1];
	init_ssl_main(algorithm, &main);
	hash_main(ac - 2, av + 2, main);
	return (0);
}
