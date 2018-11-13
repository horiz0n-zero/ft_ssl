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
    const char          *password;
	uint64_t			key;
	uint64_t			salt;
	uint64_t			vector;
}						t_des;

void    				des_pbkdf(t_des *const des,
                            const void *const pass, uint64_t salt);

#endif
