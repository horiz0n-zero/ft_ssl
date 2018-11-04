/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 16:37:25 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/04 15:47:18 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void					read_stdin(t_ssl *const ssl)
{
	char				buffer[4097];
	char				*value;
	char				*tmp;
	ssize_t				readed;

	value = NULL;
	while ((readed = read(STDIN_FILENO, buffer, 4096)) > 0)
	{
		buffer[(int)readed] = 0;
		if (!value)
			value = ft_strndup(buffer, (size_t)readed);
		else
		{
			tmp = value;
			value = ft_strjoin(value, buffer);
			free(tmp);
		}
	}
	if (readed == -1)
		error_file(ssl, "stdin");
	print_checksum(ssl, value ? value : "", "", 1);
	free(value);
}
