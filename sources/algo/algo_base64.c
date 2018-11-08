/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_base64.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 13:31:52 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/07 14:08:23 by afeuerst         ###   ########.fr       */
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

static const unsigned char g_base64de[] =
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
    7, 8, 9, 10, 11, 12,  13, 14,
    15, 16, 17, 18, 19, 20, 21, 22,
    23, 24, 25, 255, 255, 255, 255, 255,
    255, 26, 27, 28, 29, 30, 31, 32,
    33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48,
    49, 50, 51, 255, 255, 255, 255, 255
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
	*dst++ = '\n';
	*dst = 0;
}

static int              decodable_base64(const char *src, size_t len)
{
    if (len < 4)
    {
        if (!(*src == '=' && (*src >= 'a' && *src <= 'z') ||
			(*src >= 'A' && *src <= 'Z') ||
			(*src >= '0' && *src <= '9') ||
			*src == '+' || *src == '/'))
            return (1);
        *(char*)src = '=';
        return (0);
    }
    while (len--)
    {
        if (!((*src >= 'a' && *src <= 'z') ||
			(*src >= 'A' && *src <= 'Z') ||
			(*src >= '0' && *src <= '9') ||
			*src == '+' || *src == '/'))
            return (1);
    }
    return (0);
}

static void				decode_base64(unsigned char *dst, const unsigned char *src,
		const size_t len)
{
	unsigned int        i;
	unsigned char       c;

    i = -1;
	while (++i < (unsigned int)len)
    {
		if (src[i] == '=')
			break ;
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
    *dst++ = '\n';
	*dst = 0;
}

/*
static inline int		isbase64_decodable(const char *src,
		size_t len)
{
	while (len-- > 2)
	{
		if (!((*src >= 'a' && *src <= 'z') ||
			(*src >= 'A' && *src <= 'Z') ||
			(*src >= '0' && *src <= '9') ||
			*src == '+' || *src == '/'))
			return (0);
		src++;
	}
	if (!(*src == '=' || (*src >= 'a' && *src <= 'z') ||
		(*src >= 'A' && *src <= 'Z') ||
		(*src >= '0' && *src <= '9') ||
		*src == '+' || *src == '/'))
		return (0);
	src++;
	if (!(*src == '=' || (*src >= 'a' && *src <= 'z') ||
		(*src >= 'A' && *src <= 'Z') ||
		(*src >= '0' && *src <= '9') ||
		*src == '+' || *src == '/'))
		return (0);
	if (len == 1 && *src == '=' && *(src - 1) == '=')
		return (0);
	return (1);
}*/

char					*algo_base64(t_ssl *const ssl,
		const char *const src, const size_t len)
{
	void				*ptr;
	size_t				lenght;

	if (ssl->flags & FLAGS_D)
	{
		//if (!isbase64_decodable(src, len)) need other things
		//	return (INVALID);
        if (decodable_base64(src, len))
            return (INVALID);
		ptr = malloc(((len * 8) / 6) + 1);
		decode_base64(ptr, (const void*)src, len);
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
	return (ptr);
}
