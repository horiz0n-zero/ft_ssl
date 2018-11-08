/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_utility.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:37:45 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/08 16:02:22 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			exit_nonhexa(t_ssl *const ssl, const char *src, const char c)
{
	const char	*ptr;

	ptr = src;
	while (*src)
	{
		if ((*src >= 'a' && *src <= 'f') ||
			(*src >= 'A' && *src <= 'F') ||
			(*src >= '0' && *src <= '9'))
			src++;
		else
		{
			ft_fprintf(STDERR_FILENO,
					"ft_ssl: error: -%c argument non-hex digit\n", c);
			usage(ssl);
		}
	}
	if (ft_strlen(ptr) > 16)
	{
		ft_fprintf(STDERR_FILENO,
				"ft_ssl: error: -%c argument hex string is too long\n", c);
		usage(ssl);
	}
}

void			exit_flags_string(t_ssl *const ssl, const char *const src)
{
	ft_fprintf(STDERR_FILENO, "ft_ssl: illegal option -- %s\n", src);
	usage(ssl);
}
