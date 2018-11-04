/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcomparable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 14:45:34 by afeuerst          #+#    #+#             */
/*   Updated: 2018/10/27 16:14:57 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int					ft_strcomparable(const char *src, const char *compare)
{
	size_t			len;
	char			*tmp;
	int				index;

	len = ft_strlen(src);
	tmp = __builtin_alloca(len + 1);
	index = 0;
	while (len--)
	{
		if (src[index] >= 'a' && src[index] <= 'z')
			tmp[index] = src[index] - 32;
		else
			tmp[index] = src[index];
		index++;
	}
	tmp[index] = 0;
	return (ft_strcmp(tmp, compare));
}
