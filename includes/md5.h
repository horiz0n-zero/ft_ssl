/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 13:50:55 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/15 13:18:01 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include "ft_ssl.h"

typedef uint32_t	t_md5value;

typedef struct		s_md5
{
	t_md5value		a;
	t_md5value		b;
	t_md5value		c;
	t_md5value		d;
	t_md5value		ta;
	t_md5value		tb;
	t_md5value		tc;
	t_md5value		td;
}					t_md5;

void				md5_process(t_md5 *const md5, const char *src, size_t len);

#endif
