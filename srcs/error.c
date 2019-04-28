/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 19:49:22 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/04/27 21:58:46 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_ssl.h"
#include "ft_printf.h"

void		error_handler(t_err errcode, int should_exit, const char *info)
{
	if (errcode == ERR_FILE_NOT_FOUND)
		ft_printf("File not found: %s\n", info);
	else if (errcode == ERR_READ_FILE)
		ft_printf("Can't read from file: %s\n", info);
	else
		ft_printf(
	"Something terrible happened. Please, reconsider your actions\n");

	if (should_exit)
		exit(-1);
}
