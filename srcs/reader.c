/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 07:11:22 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/04/27 23:28:21 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "ft_ssl.h"
#include "ft_md5.h"
#include "memory.h"
#include "strings.h"

ssize_t	read_chunk(int fd, size_t size, void **buf)
{
	ssize_t		ret;

	ft_bzero(*buf, size);
	ret = read(fd, *buf, size);
	return (ret);
}
