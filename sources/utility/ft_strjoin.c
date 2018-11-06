/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 16:44:55 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/06 10:17:03 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char				*lstrjoin(const char *s1, size_t l1,
		const char *s2, size_t l2)
{
	const size_t	len = l1 + l2;
	char			*new;

	if (!(new = malloc(len + 1)))
		return (NULL);
	while (l1--)
		*new++ = *s1++;
	while (l2--)
		*new++ = *s2++;
	*new = 0;
	return (new - len);
}
