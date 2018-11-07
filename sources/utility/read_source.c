/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_source.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:06:22 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/06 16:44:38 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void					*ssl_input(t_ssl *const ssl, const char *const file,
		const int fd)
{
	struct stat			info;
	char				*content;

	if (fd == -1)
		return (error_file_null(ssl, file));
	if (fstat(fd, &info) == -1)
		return (error_file_null(ssl, file));
	if (!(content = malloc((size_t)info.st_size + 1)))
		return (error_file_null(ssl, file));
	if (read(fd, content, (size_t)info.st_size) != (ssize_t)info.st_size)
		return (error_file_null(ssl, file));
	close(fd);
	*(content + info.st_size) = 0;
	ssl->source_lenght = (size_t)info.st_size;
	return (content);
}

void					*ssl_file(t_ssl *const ssl, const char *const file)
{
	const int			fd = open(file, O_RDONLY);
	struct stat			info;
	char				*content;

	if (fd == -1)
		return (error_file_null(ssl, file));
	if (fstat(fd, &info) == -1)
		return (error_file_null(ssl, file));
	if (!(content = malloc((size_t)info.st_size + 1)))
		return (error_file_null(ssl, file));
	if (read(fd, content, (size_t)info.st_size) != (ssize_t)info.st_size)
		return (error_file_null(ssl, file));
	close(fd);
	*(content + info.st_size) = 0;
	ssl->source_lenght = (size_t)info.st_size;
	return (content);
}

void					ssl_input_print(t_ssl *const ssl, const char *const file,
		const int fd)
{
	struct stat			info;
	char				*content;

	if (fd == -1)
		return (error_file(ssl, file));
	if (fstat(fd, &info) == -1)
		return (error_file(ssl, file));
	if (!(content = malloc((size_t)info.st_size + 1)))
		return (error_file(ssl, file));
	if (read(fd, content, (size_t)info.st_size) != (ssize_t)info.st_size)
		return (error_file(ssl, file));
	close(fd);
	*(content + info.st_size) = 0;
	ssl->source_lenght = (size_t)info.st_size;
	print_checksum(ssl, content, file, 0);
	free(content);
}

void					ssl_file_print(t_ssl *const ssl, const char *const file)
{
	const int			fd = open(file, O_RDONLY);
	struct stat			info;
	char				*content;

	if (fd == -1)
		return (error_file(ssl, file));
	if (fstat(fd, &info) == -1)
		return (error_file(ssl, file));
	if (!(content = malloc((size_t)info.st_size + 1)))
		return (error_file(ssl, file));
	if (read(fd, content, (size_t)info.st_size) != (ssize_t)info.st_size)
		return (error_file(ssl, file));
	close(fd);
	*(content + info.st_size) = 0;
	ssl->source_lenght = (size_t)info.st_size;
	print_checksum(ssl, content, file, 0);
	free(content);
}
