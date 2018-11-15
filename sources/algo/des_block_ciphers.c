/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_block_ciphers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 13:46:37 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/15 14:27:40 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

static inline void			des_cbc(t_ssl *const ssl, register t_des *const des,
		register uint64_t *ptr, register size_t len)
{
	register uint64_t		lblock;
	register uint64_t		result;

	lblock = des->vector;
	if (ssl->flags & FLAGS_D)
	{
		while (len >= sizeof(*ptr))
		{
			len -= sizeof(*ptr);
			result = des_process(des, *ptr, 1) ^ lblock;
			lblock = *ptr;
			*ptr++ = result;
		}
	}
	else
	{
		while (len >= sizeof(*ptr))
		{
			len -= sizeof(*ptr);
			lblock = des_process(des, *ptr ^ lblock, 0);
			*ptr++ = lblock;
		}
	}
}

void						des_block_ciphers(t_ssl *const ssl, void *const src,
		size_t len)
{
	register uint64_t		*ptr;
	register t_des *const	des = ssl->required;

	ptr = src;
	if (ssl->algo->settings & ECB)
	{
		while (len >= 8)
		{
			len -= sizeof(*ptr);
			*ptr = des_process(des, *ptr, ssl->flags & FLAGS_D ? 1 : 0);
			ptr++;
		}
	}
	else if (ssl->algo->settings & CBC)
		des_cbc(ssl, des, ptr, len);
}
