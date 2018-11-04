/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 15:05:16 by afeuerst          #+#    #+#             */
/*   Updated: 2018/10/31 10:41:56 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void				usage(t_ssl *const ssl)
{
	(void)ssl;
	write(STDERR_FILENO, "usage: command [-pqr] [-s string] [files ...]",
			sizeof("usage: command [-pqr] [-s string] [files ...]"));
	exit(EXIT_FAILURE);
}

void				exit_flags(t_ssl *const ssl, const char c)
{
	write(STDERR_FILENO, "ft_ssl: illegal option -- ",
			sizeof("ft_ssl: illegal option -- "));
	write(STDERR_FILENO, &c, 1);
	write(STDERR_FILENO, "\n", 1);
	usage(ssl);
}

void				exit_nostring(t_ssl *const ssl)
{
	write(STDERR_FILENO, "ft_ssl: option requires an argument -- s\n",
			sizeof("ft_ssl: option requires an argument -- s\n"));
	usage(ssl);
}
