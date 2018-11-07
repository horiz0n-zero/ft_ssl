/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 16:37:25 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/06 16:33:35 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void					*read_stdin(t_ssl *const ssl)
{
	char				buffer[4097];
	char				*value;
	char				*tmp;
	ssize_t				readed;
	ssize_t				total;

	total = 0;
	value = NULL;
	while ((readed = read(STDIN_FILENO, buffer, 4096)) > 0)
	{
		!(buffer[(int)readed] = 0) && (total += readed);
		if (!value)
			value = ft_strndup(buffer, (size_t)readed);
		else
		{
			tmp = value;
			value = lstrjoin(value, (total - readed), buffer, readed);
			free(tmp);
		}
	}
	if (readed == -1)
		error_file(ssl, "stdin");
	ssl->source_lenght = (size_t)total;
	return (value);
}

void					read_stdin_print(t_ssl *const ssl)
{
	char				buffer[4097];
	char				*value;
	char				*tmp;
	ssize_t				readed;
	ssize_t				total;

	total = 0;
	value = NULL;
	while ((readed = read(STDIN_FILENO, buffer, 4096)) > 0)
	{
		!(buffer[(int)readed] = 0) && (total += readed);
		if (!value)
			value = ft_strndup(buffer, (size_t)readed);
		else
		{
			tmp = value;
			value = lstrjoin(value, (total - readed), buffer, readed);
			free(tmp);
		}
	}
	if (readed == -1)
		error_file(ssl, "stdin");
	ssl->source_lenght = (size_t)total;
	print_checksum(ssl, value, value, 1);
	free(value);
}
