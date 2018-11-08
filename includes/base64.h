/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 09:44:28 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/08 09:29:21 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE64_H
# define BASE64_H

# include "ft_ssl.h"

# define INVALID "Invalid character in input stream.\n"

void		decode_base64(unsigned char *dst, const unsigned char *src,
		const size_t len, unsigned char c);

int			decodable_base64(const char *src, size_t len);

#endif
