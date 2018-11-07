/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_strerror.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 15:46:51 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/06 16:47:13 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include <errno.h>
#include <string.h>

void					error_file(t_ssl *const ssl, const char *const file)
{
	const char *const	err = strerror(errno);

	(void)ssl;
	ft_fprintf(STDERR_FILENO, "ft_ssl: %s: %s\n", file, err);
}

void					*error_file_null(t_ssl *const ssl, const char *const file)
{
	const char *const	err = strerror(errno);

	(void)ssl;
	ft_fprintf(STDERR_FILENO, "ft_ssl: %s: %s\n", file, err);
	return (NULL);
}
