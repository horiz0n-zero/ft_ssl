/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_md5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 14:36:21 by afeuerst          #+#    #+#             */
/*   Updated: 2018/10/31 13:36:23 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "md5.h"

static void				md5_update(t_md5 *const md5, const char *src,
		const size_t len)
{
	size_t				new_len;
	uint64_t			value;
	char				*ptr;

	new_len = len * 8 + 1;
	while (new_len % 512 != 448)
		new_len++;
	new_len /= 8;
	new_len += sizeof(uint64_t);
	ptr = malloc(new_len);
	ft_memset(ptr, new_len);
	ft_memcpy(ptr, src, len);
	ptr[len] = (char)128;
	value = (uint64_t)len * 8;
	ft_memcpy(ptr + (new_len - sizeof(uint64_t)), &value, sizeof(uint64_t));
	md5_process(md5, ptr, new_len);
	free(ptr);
}

static char				*printable_digest(const unsigned char *const digest)
{
	static char			printable[33];
	unsigned char		current;
	int					index;
	int					i;
	static const char	hexa[] = "0123456789abcdef";

	index = 0;
	i = 0;
	while (index < 16)
	{
		current = digest[index++];
		printable[i + 1] = hexa[(int)current % 16];
		current /= 16;
		printable[i] = hexa[(int)current % 16];
		i += 2;
	}
	printable[32] = 0;
	return (printable);
}

char					*algo_md5(const char *const src)
{
	struct s_md5		md5;
	char				digest[16];

	md5.a = 0x67452301;
	md5.b = 0xefcdab89;
	md5.c = 0x98badcfe;
	md5.d = 0x10325476;
	md5_update(&md5, src, ft_strlen(src));
	((t_md5value*)digest)[0] = md5.a;
	((t_md5value*)digest)[1] = md5.b;
	((t_md5value*)digest)[2] = md5.c;
	((t_md5value*)digest)[3] = md5.d;
	return (printable_digest((const unsigned char*)digest));
}
