/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_sha256.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 14:37:08 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/04 15:40:18 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"

static void					sha256_update(t_sha256 *const sha,
		uint8_t *const data, const size_t length)
{
	size_t					i;

	i = 0;
	while (i < length)
	{
		sha->data[sha->data_length++] = data[i];
		if (sha->data_length == 64)
		{
			sha256_transform(sha, sha->data);
			sha->bit_length += 512;
			sha->data_length = 0;
		}
		i++;
	}
}

static void					sha256_finaltransform(t_sha256 *const sha,
		uint8_t *const hash, uint32_t i)
{
	sha->bit_length += sha->data_length * 8;
	sha->data[63] = sha->bit_length;
	sha->data[62] = sha->bit_length >> 8;
	sha->data[61] = sha->bit_length >> 16;
	sha->data[60] = sha->bit_length >> 24;
	sha->data[59] = sha->bit_length >> 32;
	sha->data[58] = sha->bit_length >> 40;
	sha->data[57] = sha->bit_length >> 48;
	sha->data[56] = sha->bit_length >> 56;
	sha256_transform(sha, sha->data);
	while (i < 4)
	{
		hash[i] = (sha->state[0] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 4] = (sha->state[1] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 8] = (sha->state[2] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 12] = (sha->state[3] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 16] = (sha->state[4] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 20] = (sha->state[5] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 24] = (sha->state[6] >> (24 - i * 8)) & 0x000000ff;
		hash[i + 28] = (sha->state[7] >> (24 - i * 8)) & 0x000000ff;
		i++;
	}
}

static void					sha256_finish(t_sha256 *const sha,
		uint8_t *const hash)
{
	uint32_t				i;

	i = sha->data_length;
	if (sha->data_length < 56)
	{
		sha->data[i++] = 0x80;
		while (i < 56)
		{
			sha->data[i++] = 0x00;
		}
	}
	else
	{
		sha->data[i++] = 0x80;
		while (i < 64)
		{
			sha->data[i++] = 0x00;
		}
		sha256_transform(sha, sha->data);
		ft_memset((void*)sha->data, 56);
	}
	sha256_finaltransform(sha, hash, 0);
}

static char					*printable_digest(const unsigned char *const digest)
{
	static char				printable[65];
	unsigned char			current;
	int						index;
	int						i;
	static const char		hexa[] = "0123456789abcdef";

	index = 0;
	i = 0;
	while (index < 32)
	{
		current = digest[index++];
		printable[i + 1] = hexa[(int)current % 16];
		current /= 16;
		printable[i] = hexa[(int)current % 16];
		i += 2;
	}
	printable[64] = 0;
	return (printable);
}

char						*algo_sha256(const char *const src)
{
	t_sha256				sha;
	static unsigned char	hash[33];

	sha.data_length = 0;
	sha.bit_length = 0;
	sha.state[0] = 0x6a09e667;
	sha.state[1] = 0xbb67ae85;
	sha.state[2] = 0x3c6ef372;
	sha.state[3] = 0xa54ff53a;
	sha.state[4] = 0x510e527f;
	sha.state[5] = 0x9b05688c;
	sha.state[6] = 0x1f83d9ab;
	sha.state[7] = 0x5be0cd19;
	sha256_update(&sha, (void*)src, ft_strlen(src));
	sha256_finish(&sha, (void*)hash);
	hash[32] = 0;
	return (printable_digest(hash));
}
