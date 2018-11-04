/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_strerror.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 15:46:51 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/01 14:51:40 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <errno.h>
#include <string.h>

void					error_file(t_ssl *const ssl, const char *const file)
{
	const char *const	err = strerror(errno);

	(void)ssl;
	write(STDERR_FILENO, "ft_ssl: ", 8);
	write(STDERR_FILENO, file, ft_strlen(file));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, err, ft_strlen(err));
	write(STDERR_FILENO, "\n", 1);
}
