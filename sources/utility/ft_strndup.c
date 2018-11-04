/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 16:42:33 by afeuerst          #+#    #+#             */
/*   Updated: 2018/10/27 16:43:56 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char			*ft_strndup(const char *const src, const size_t len)
{
	char		*new;
	size_t		i;

	i = 0;
	if (!(new = malloc(len + 1)))
		return (NULL);
	while (i < len)
	{
		new[i] = src[i];
		i++;
	}
	new[i] = 0;
	return (new);
}
