/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 09:45:55 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/19 09:48:53 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libprintf.h"
#include <fcntl.h>

static void					ft_fprintfunction(const char *const src,
		t_printinfo *const info)
{
	const int				fd = open((const char*)info->free, O_WRONLY);

	info->total_len--;
	info->data = write(fd, src, info->total_len);
	close(fd);
}

int							ft_pprintf(const char *const path,
		const char *format, ...)
{
	t_printdata				*element;
	t_printinfo				info;
	va_list					args;

	element = NULL;
	info.first_element = &element;
	va_start(args, format);
	info.args = &args;
	info.function = ft_fprintfunction;
	info.total_len = 1;
	info.data = 0;
	info.free = (uint64_t)path;
	printf_exec(format, &info, info.first_element);
	va_end(args);
	return ((int)info.total_len);
}
