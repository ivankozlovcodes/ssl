/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/16 12:38:07 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/04/24 08:06:59 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SLL_H
# define FT_SLL_H

#include "stddef.h"

# define USAGE "usage: ft_ssl command [command opts] [command args]"

char	*read_chunk(int fd, size_t size);

#endif