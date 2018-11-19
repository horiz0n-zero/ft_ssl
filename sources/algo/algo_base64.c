/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_base64.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 13:31:52 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/19 10:28:51 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"

static const char		g_base64[] =
{
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3',
	'4', '5', '6', '7', '8', '9', '+', '/'
};

static void				encode_base64(char *dst, const unsigned char *src,
		size_t len)
{
	while (len > 2)
	{
		len -= 3;
		*dst++ = g_base64[(int)((src[0] >> 2) & 0x3f)];
		*dst++ = g_base64[(int)(((src[0] << 4) + (src[1] >> 4)) & 0x3f)];
		*dst++ = g_base64[(int)(((src[1] << 2) + (src[2] >> 6)) & 0x3f)];
		*dst++ = g_base64[(int)((src[2] & 0x3f))];
		src += 3;
	}
	if (len == 2)
	{
		*dst++ = g_base64[(int)((src[0] >> 2) & 0x3f)];
		*dst++ = g_base64[(int)((src[0] << 4) + (src[1] >> 4)) & 0x3f];
		*dst++ = g_base64[(int)((src[1] << 2) & 0x3f)];
		*dst++ = '=';
	}
	else if (len == 1)
	{
		*dst++ = g_base64[(int)(src[0] >> 2) & 0x3f];
		*dst++ = g_base64[(int)(src[0] << 4) & 0x3f];
		*dst++ = '=';
		*dst++ = '=';
	}
	*dst = 0;
}

char					*algo_base64(t_ssl *const ssl,
		const char *const src, const size_t len)
{
	void				*ptr;
	size_t				lenght;

	if (ssl->flags & FLAGS_D)
	{
		if (decodable_base64(src, len))
		{
			write(STDERR_FILENO, INVALID, sizeof(INVALID));
			return (ft_strsub(""));
		}
		ptr = malloc(((len * 8) / 6) + 1);
		ft_memset(ptr, ((len * 8) / 6) + 1);
		decode_base64(ptr, (const void*)src, len, 0);
	}
	else
	{
		lenght = (len / 3) * 4;
		if ((len - (len / 3) * 3) > 0)
			ptr = malloc(lenght + 6);
		else
			ptr = malloc(lenght + 2);
		encode_base64(ptr, (const void*)src, len);
	}
	ssl->source_lenght = ft_strlen(ptr);
	return (ptr);
}
