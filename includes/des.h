/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:00:10 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/12 11:31:35 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_H
# define DES_H

# include "ft_ssl.h"

typedef struct			s_des
{
	uint64_t			key;
	uint64_t			salt;
	uint64_t			vector;
}						t_des;

uint64_t				des_pbkdf(const uint8_t *pass, uint64_t salt, int itr);

#endif
