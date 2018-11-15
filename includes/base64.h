/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 09:44:28 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/15 16:53:25 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE64_H
# define BASE64_H

# include "ft_ssl.h"

# define INVALID "Invalid character in input stream.\n"
# define BASE64UPAZ "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define BASE64LOAZ "abcdefghijklmnopqrstuvwxyz"
# define BASE6409 "0123456789+/"
# define BASE64 BASE64LOAZ BASE64UPAZ BASE6409

# define WHITE_SPACE " \t\n\v\f\r"

void		decode_base64(unsigned char *dst, const unsigned char *src,
		const size_t len, unsigned char c);

int			decodable_base64(const char *src, size_t len);

#endif
