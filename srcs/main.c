/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 07:55:36 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/04/24 08:00:57 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "ft_ssl.h"
#include "ft_printf.h"

int		main(int ac, char *av[])
{
	int		fd;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		ft_printf("%s\n", read_chunk(fd, 512));
		close(fd);
	}
	return (0);
}
