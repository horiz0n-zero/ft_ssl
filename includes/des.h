/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:00:10 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/26 10:53:20 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_H
# define DES_H

# include "ft_ssl.h"

typedef struct			s_des
{
	const char			*password;
	uint64_t			key;
	uint64_t			salt;
	uint64_t			vector;
	uint64_t			subkeys[16];
}						t_des;

typedef struct			s_tables
{
	const uint64_t		exp[48];
	const uint64_t		sbox[8][64];
	const uint64_t		psbox[32];
}						t_tables;

typedef struct			s_subkeys
{
	const uint64_t		pc1[56];
	const uint64_t		pc2[48];
	const int			iteshift[16];
}						t_subkeys;

void					des_pbkdf(t_des *const des,
		const void *const pass, uint64_t salt);

uint64_t				des_process(t_des *const des,
		uint64_t block, const int decrypt);
uint32_t				des_f(const uint32_t r,
		const uint64_t k);

void					des_block_ciphers(t_ssl *const ssl,
		void *const src, size_t len);
void					des_read_header(t_ssl *const ssl,
		t_des *const des, const uint64_t *src);
void					*des_padding(t_ssl *const ssl,
		const void *const src, const int decrypt);

# define LB32_MASK 0x00000001
# define LB64_MASK 0x0000000000000001
# define L64_MASK  0x00000000ffffffff
# define MAGIC_DES_NUMBER (uint64_t)0x53616c7465645f5f

#endif
