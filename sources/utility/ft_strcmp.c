/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 14:51:27 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/15 16:32:59 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char				*ft_strsub(const char *src)
{
	size_t			len;
	char			*ptr;

	len = 0;
	while (src[len])
		len++;
	ptr = malloc(len + 1);
	len = 0;
	while (src[len])
		ptr[len] = src[len];
	ptr[len] = 0;
	return (ptr);
}

int					ft_cinstr(const char *src, const char c)
{
	while (*src)
	{
		if (*src++ == c)
			return (1);
	}
	return (0);
}

int					ft_strcmp(register const char *s1, register const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((int)(*s1 - *s2));
}
