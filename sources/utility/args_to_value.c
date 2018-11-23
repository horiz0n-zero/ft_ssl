/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_to_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:07:05 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/22 16:05:20 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static inline uint64_t			raw_hexa(register const char c)
{
	if (c >= '0' && c <= '9')
		return ((uint64_t)c - '0');
	else if (c >= 'a' && c <= 'z')
		return ((uint64_t)c - 'a' + 10);
	return ((uint64_t)c - 'A' + 10);
}

uint64_t						ft_hexa_binary(register const char *src)
{
	register uint64_t			r;

	r = 0;
	while (*src)
	{
		r |= raw_hexa(*src++);
		if (*src)
			r <<= 4;
	}
	return (r);
}

static inline void				src_upper(char *src)
{
	while (*src)
	{
		if (*src >= 'a' && *src <= 'z')
			*src = 'A' + (*src - 'a');
		src++;
	}
}

void							des_hexa(const char *src, uint64_t *const value)
{
	const uint64_t				size = 16 - (uint64_t)ft_strlen(src);

	*value = 0;
	src_upper((char*)src);
	while (*src)
	{
		*value += ((*src >= 'A') ?
			(uint64_t)*src - 'A' + 0xa :
			(uint64_t)*src - '0');
		if (*++src)
			*value *= 16;
	}
	*value <<= size * 4;
}
