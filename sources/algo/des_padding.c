/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_padding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 13:16:39 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/26 10:54:21 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

static inline void				des_crypt(t_ssl *const ssl,
		register void *dst)
{
	uint64_t					size;
	uint64_t					buffer;

	size = 8 - ((uint64_t)ssl->source_lenght % 8);
	if (!size)
		size = 8;
	buffer = 0;
	if (size != 8)
		ssl->source_lenght += (uint64_t)size;
	buffer <<= (size * 8);
	buffer |= (1 << (size * 8 - 1));
	ft_memcpy(&buffer, ((char*)dst) + ssl->source_lenght - (8 - size),
			(8 - size));
}

static inline void				des_decrypt(t_ssl *const ssl,
		register uint64_t *dst)
{
	uint64_t					buffer;
	uint64_t					padding;

	buffer = *(dst + (ssl->source_lenght / sizeof(uint64_t)));
	padding = 0;
	while (!(buffer & 0xFF))
	{
		buffer >>= 8;
		padding++;
	}
	buffer >>= 8;
	padding++;
	if (padding != 8)
		ft_memcpy(dst, ((char*)dst) + ssl->source_lenght - (8 - padding), (8 - padding));
}

void							*des_padding(t_ssl *const ssl, const void *const src,
		const int decrypt)
{
	register uint64_t			*ptr;

	ptr = malloc(ssl->source_lenght + sizeof(uint64_t));
	ft_memcpy(ptr, src, ssl->source_lenght);
	*((uint64_t*)(((char*)ptr) + ssl->source_lenght)) = 0;
	if (decrypt)
		des_decrypt(ssl, ptr);
	else
		des_crypt(ssl, ptr);
	return (ptr);
}
