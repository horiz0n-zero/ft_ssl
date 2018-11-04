/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_body.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 14:26:25 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/01 11:07:33 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

static const t_md5value			g_k[] =
{
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

static const t_md5value			g_s[] =
{
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

static inline void				md5_loop2(t_md5 *const md5, const t_md5value i,
		const t_md5value f)
{
	md5->ta = md5->td;
	md5->td = md5->tc;
	md5->tc = md5->tb;
	md5->tb = md5->tb + ((f << g_s[(int)i]) | (f >> (32 - g_s[(int)i])));
}

static void						md5_loop(t_md5 *const md5, const t_md5value i,
		const t_md5value *const m)
{
	t_md5value					f;
	t_md5value					g;

	if (i <= 15)
	{
		f = (md5->tb & md5->tc) | ((~md5->tb) & md5->td);
		g = i;
	}
	else if (i <= 31)
	{
		f = (md5->td & md5->tb) | ((~md5->td) & md5->tc);
		g = (5 * i + 1) % 16;
	}
	else if (i <= 47)
	{
		f = md5->tb ^ md5->tc ^ md5->td;
		g = (3 * i + 5) % 16;
	}
	else
	{
		f = md5->tc ^ (md5->tb | (~md5->td));
		g = (7 * i) % 16;
	}
	f = f + md5->ta + g_k[(int)i] + m[(int)g];
	md5_loop2(md5, i, f);
}

void							md5_process(t_md5 *const md5, const char *src,
		size_t len)
{
	t_md5value					i;
	size_t						offset;

	offset = 0;
	while (1)
	{
		offset += 64;
		if (offset > len)
			break ;
		md5->ta = md5->a;
		md5->tb = md5->b;
		md5->tc = md5->c;
		md5->td = md5->d;
		i = 0;
		while (i < 64)
			md5_loop(md5, i++, (const void*)src);
		md5->a = md5->a + md5->ta;
		md5->b = md5->b + md5->tb;
		md5->c = md5->c + md5->tc;
		md5->d = md5->d + md5->td;
		src += 64;
	}
}
