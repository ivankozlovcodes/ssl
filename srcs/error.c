/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivankozlov <ivankozlov@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 19:49:22 by ivankozlov        #+#    #+#             */
/*   Updated: 2019/05/04 13:24:58 by ivankozlov       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ft_ssl.h"

#include "ft_printf.h"

void		error_handler(t_err errcode, int should_exit, const char *info)
{
	if (errcode != ERR_INVALID_COMMAND && errcode != ERR_NO_COMMAND)
		ft_printf("%s %s: ", PREFIX, g_hash_func_name);
	if (errcode == ERR_FILE_NOT_FOUND)
		ft_printf("%s: No such file or directory\n", info);
	else if (errcode == ERR_READ_FILE)
		ft_printf("Can't read from file: %s\n", info);
	else if (errcode == ERR_ILLEGAL_OPTION)
		ft_printf("illegal option -- %c\n%s\n", *info, USAGE);
	else if (errcode == ERR_NO_ARG)
		ft_printf("option requires an argument -- %s\n%s\n", info, USAGE);
	else if (errcode == ERR_INVALID_COMMAND)
		ft_printf("Error: %s is invalid command.\n%s", info, COMMANDS_MSG);
	else if (errcode == ERR_NO_COMMAND)
		ft_printf("%s\n", USAGE);
	else
		ft_printf(
	"Something terrible happened. Please, reconsider your actions\n");
	if (should_exit)
		exit(-1);
}
