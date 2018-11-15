/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:00:10 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/15 10:41:59 by afeuerst         ###   ########.fr       */
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

# define LB32_MASK 0x00000001
# define LB64_MASK 0x0000000000000001
# define L64_MASK  0x00000000ffffffff

#endif
