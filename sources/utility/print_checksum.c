/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_checksum.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 15:37:17 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/06 13:33:33 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static inline void		r_print(const char *const src, const char *const name)
{
	if (src == name)
	{
		write(STDOUT_FILENO, " \"", 2);
		write(STDOUT_FILENO, name, ft_strlen(name));
		write(STDOUT_FILENO, "\"", 1);
	}
	else
	{
		write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, name, ft_strlen(name));
	}
}

static inline void		normal_print(const char *const src,
		const char *const name)
{
	if (name == src)
	{
		write(STDOUT_FILENO, " (\"", 3);
		write(STDOUT_FILENO, name, ft_strlen(name));
		write(STDOUT_FILENO, "\") = ", 5);
	}
	else
	{
		write(STDOUT_FILENO, " (", 2);
		write(STDOUT_FILENO, name, ft_strlen(name));
		write(STDOUT_FILENO, ") = ", 4);
	}
}

void					print_checksum(t_ssl *const ssl, const char *const src,
		const char *const name,
		const int isflagsp)
{
	char				*checksum;

	if (src == name && !isflagsp)
		ssl->source_lenght = ft_strlen(src);
	checksum = ssl->algo->checksum(ssl, src, ssl->source_lenght);
	if (ssl->flags & FLAGS_Q || isflagsp)
		write(STDOUT_FILENO, checksum, ft_strlen(checksum));
	else if (ssl->flags & FLAGS_R)
	{
		write(STDOUT_FILENO, checksum, ft_strlen(checksum));
		r_print(src, name);
	}
	else
	{
		write(STDOUT_FILENO, ssl->algo->algo, ft_strlen(ssl->algo->algo));
		normal_print(src, name);
		write(STDOUT_FILENO, checksum, ft_strlen(checksum));
	}
	write(STDOUT_FILENO, "\n", 1);
}
