/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 14:32:40 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/04 15:51:14 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static const char		g_available_flags[256] =
{
	['p'] = FLAGS_P,
	['q'] = FLAGS_Q,
	['r'] = FLAGS_R,
	['s'] = FLAGS_S
};

static void				ssl_file(t_ssl *const ssl, const char *const file)
{
	const int			fd = open(file, O_RDONLY);
	struct stat			info;
	char				*content;

	if (fd == -1)
		return (error_file(ssl, file));
	if (stat(file, &info) == -1)
		return (error_file(ssl, file));
	if (!(content = malloc((size_t)info.st_size + 1)))
		return (error_file(ssl, file));
	if (read(fd, content, (size_t)info.st_size) != (ssize_t)info.st_size)
		return (error_file(ssl, file));
	close(fd);
	*(content + info.st_size) = 0;
	print_checksum(ssl, content, file, 0);
	free(content);
}

static inline void		ssl_dowork(t_ssl *const ssl, int current_flags)
{
	char				*tmp;
	int					state;

	state = 0;
	while (*ssl->argv)
	{
		current_flags = 0;
		tmp = *ssl->argv++;
		if (*tmp == '-' && !(state & STATE_FILE) && ++tmp)
		{
			if (*tmp == '-' && (state |= STATE_FILE))
				continue ;
			while (*tmp)
				current_flags |= g_available_flags[(int)*tmp++];
			if (current_flags & FLAGS_P)
				read_stdin(ssl);
			if (current_flags & FLAGS_S)
			{
				print_checksum(ssl, *ssl->argv, *ssl->argv, 0);
				ssl->argv++;
			}
		}
		else
			ssl_file(ssl, tmp);
	}
}

static void				ssl_read_flags(t_ssl *const ssl, char **argv)
{
	char				*tmp;

	while (*argv && **argv == '-')
	{
		tmp = *argv++;
		if (*++tmp == '-')
			break ;
		while (*tmp)
		{
			if (g_available_flags[(int)*tmp])
			{
				ssl->flags |= g_available_flags[(int)*tmp];
				if (*tmp++ == 's')
					!*argv ? exit_nostring(ssl) : argv++;
			}
			else
				exit_flags(ssl, *tmp);
		}
	}
	if (!*argv && !(ssl->flags & FLAGS_P) && !(ssl->flags & FLAGS_S))
		read_stdin(ssl);
}

int						main(int argc, char **argv)
{
	t_ssl				ssl;

	(void)argc;
	ssl.argv = ++argv;
	ssl.flags = 0;
	ssl.algo = NULL;
	ssl_get_algo(&ssl, *argv++);
	ssl_read_flags(&ssl, argv);
	ssl_dowork(&ssl, 0);
	return (EXIT_SUCCESS);
}
