/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_des.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:11:40 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/20 14:31:32 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

static const t_subkeys		g_subkeys =
{
	{57, 49, 41, 33, 25, 17, 9, 1, 58, 50,
		42, 34, 26, 18, 10, 2, 59, 51, 43, 35,
		27, 19, 11, 3, 60, 52, 44, 36, 63, 55,
		47, 39, 31, 23, 15, 7, 62, 54, 46, 38,
		30, 22, 14, 6, 61, 53, 45, 37, 29, 21,
		13, 5, 28, 20, 12, 4},
	{14, 17, 11, 24, 1, 5, 3, 28, 15, 6,
		21, 10, 23, 19, 12, 4, 26, 8, 16, 7,
		27, 20, 13, 2, 41, 52, 31, 37, 47,
		55, 30, 40, 51, 45, 33, 48, 44, 49,
		39, 56, 34, 53, 46, 42, 50, 36, 29, 32},
	{1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1}
};

static inline void			subkeys_schedule(t_des *const des,
		const int i, uint32_t *const c, uint32_t *const d)
{
	int						j;
	uint64_t				permu;

	j = 0;
	while (j < g_subkeys.iteshift[i])
	{
		*c = (0x0fffffff & (*c << 1)) | (0x00000001 & (*c >> 27));
		*d = (0x0fffffff & (*d << 1)) | (0x00000001 & (*d >> 27));
		j++;
	}
	permu = (((uint64_t)*c) << 28) | (uint64_t)*d;
	des->subkeys[i] = 0;
	j = 0;
	while (j < 48)
	{
		des->subkeys[i] <<= 1;
		des->subkeys[i] |= (permu >> (56 - g_subkeys.pc2[j])) & LB64_MASK;
		j++;
	}
}

static void					subkeys_calculation(t_des *const des,
		const uint64_t key)
{
	uint64_t				permu;
	int						i;
	uint32_t				c;
	uint32_t				d;

	permu = 0;
	i = 0;
	while (i < 56)
	{
		permu <<= 1;
		permu |= (key >> (64 - g_subkeys.pc1[i])) & LB64_MASK;
		i++;
	}
	c = (uint32_t)((permu >> 28) & 0x000000000fffffff);
	c = (uint32_t)(permu & 0x000000000fffffff);
	i = 0;
	while (i < 16)
	{
		subkeys_schedule(des, i, &c, &d);
		i++;
	}
}

static void					*des_padding(const char *const src,
		const size_t len, const int decrypt)
{
	void *const				ptr = malloc(len + sizeof(uint64_t) + 1);
	size_t					padding;

	(void)decrypt;
	padding = 0;
	ft_memset(ptr, len + sizeof(uint64_t) + 1);
	return (ptr);
}
// echo -n "content" | openssl des -pass "pass:password" -S 4223 | base64 ->
// echo -n "content" | openssl des -pass "pass:password" -S 4223 -a
// <-> echo -n "content" | openssl des -pass "pass:password" -S 4223 -a > encrypted
// cat encrypted | openssl des -pass "pass:password" -S 4223 -a -d
// cat encrypted | base64 -D | openssl des -pass "pass:password" -S 4223 -d

char						*algo_des(t_ssl *const ssl, const char *const src,
		const size_t len)
{
	struct s_des *const		des = ssl->required;
	void					*proc;
	void					*tmp;
	const int				decrypt = ssl->flags & FLAGS_D ? 1 : 0;

	subkeys_calculation(des, des->key);
	if (ssl->flags & FLAGS_A && decrypt && (tmp = algo_base64(ssl, src, len)))
	{
		proc = des_padding(tmp, ssl->source_lenght, decrypt);
		des_block_ciphers(ssl, proc, ssl->source_lenght);
		free(tmp);
	}
	else
	{
		proc = des_padding(src, ssl->source_lenght, decrypt);
		des_block_ciphers(ssl, proc, ssl->source_lenght);
	}
	if (ssl->flags & FLAGS_A && !decrypt)
	{
		tmp = algo_base64(ssl, proc, ssl->source_lenght);
		free(proc);
		return (tmp);
	}
	return (proc);
}
