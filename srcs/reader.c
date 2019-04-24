/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 07:11:22 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/04/24 08:07:51 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "strings.h"

char	*read_chunk(int fd, size_t size)
{
	int		ret;
	int 	buffer[size + 1];

	ret = read(fd, buffer, size);
	buffer[ret] = '\0';
	return ft_strdup((const char *)buffer);
}
