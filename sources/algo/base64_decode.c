/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_decode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 09:22:26 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/19 10:45:17 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"

static const unsigned char	g_base64de[] =
{
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 62, 255, 255, 255, 63,
	52, 53, 54, 55, 56, 57, 58, 59,
	60, 61, 255, 255, 255, 255, 255, 255,
	255, 0, 1, 2, 3, 4, 5, 6,
	7, 8, 9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22,
	23, 24, 25, 255, 255, 255, 255, 255,
	255, 26, 27, 28, 29, 30, 31, 32,
	33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48,
	49, 50, 51, 255, 255, 255, 255, 255
};

int							decodable_base64(const char *src, size_t len)
{
	size_t					real;

	real = 0;
	while (len-- && *src != '=')
	{
		if (ft_cinstr(WHITE_SPACE, *src))
		{
			src++;
			continue ;
		}
		if (!ft_cinstr(BASE64, *src++))
			return (1);
		real++;
	}
	if (real < 4)
		*((char*)src) = '=';
	return (0);
}

static inline int			white_skip(unsigned int *const i, size_t *const len)
{
	*len = *len - 1;
	*i = *i - 1;
	return (1);
}

void						decode_base64(unsigned char *dst,
		const unsigned char *src, size_t len, unsigned char c)
{
	unsigned int			i;

	i = -1;
	while (++i < (unsigned int)len && src[i] != '=')
	{
		if (ft_cinstr(WHITE_SPACE, src[i]) && src++ && white_skip(&i, &len))
			continue ;
		c = g_base64de[(int)src[i]];
		if ((i & 0x3) == 0)
			*dst = (c << 2) & 0xFF;
		else if ((i & 0x3) == 1)
		{
			*dst++ |= (c >> 4) & 0x3;
			*dst = (c & 0xF) << 4;
		}
		else if ((i & 0x3) == 2)
		{
			*dst++ |= (c >> 2) & 0xF;
			*dst = (c & 0x3) << 6;
		}
		else
			*dst++ |= c;
	}
	*++dst = 0;
}
