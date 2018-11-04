/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/31 09:55:17 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/04 15:30:51 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_H
# define SHA256_H

# include "ft_ssl.h"

# define RL(x, y) ((x << y) | (x >> (32 - y)))
# define RR(x, y) ((x >> y) | (x << (32 - y)))
# define C(x, y, z) ((x & y) ^ ((~x) & z))
# define M(x,y,z) ((x & y) ^ (x & z) ^ (y & z))
# define E0(x) (RR(x, 2) ^ RR(x, 13) ^ RR(x, 22))
# define E1(x) (RR(x, 6) ^ RR(x, 11) ^ RR(x, 25))
# define S0(x) (RR(x, 7) ^ RR(x, 18) ^ (x >> 3))
# define S1(x) (RR(x, 17) ^ RR(x, 19) ^ (x >> 10))

typedef struct		s_sha256
{
	uint8_t			data[64];
	size_t			data_length;
	size_t			bit_length;
	uint32_t		state[8];
	uint32_t		a;
	uint32_t		b;
	uint32_t		c;
	uint32_t		d;
	uint32_t		e;
	uint32_t		f;
	uint32_t		g;
	uint32_t		h;
}					t_sha256;

void				sha256_transform(t_sha256 *const sha, uint8_t *const data);

#endif
