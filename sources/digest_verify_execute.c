/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest_verify_execute.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 09:37:54 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/06 16:34:00 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static const char		g_available_flags[256] =
{
	['p'] = FLAGS_P,
	['P'] = FLAGS_P,
	['q'] = FLAGS_Q,
	['Q'] = FLAGS_Q,
	['r'] = FLAGS_R,
	['R'] = FLAGS_R,
	['s'] = FLAGS_S,
	['S'] = FLAGS_S
};

void					digest_execute(t_ssl *const ssl, int current_flags)
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
				read_stdin_print(ssl);
			if (current_flags & FLAGS_S)
			{
				print_checksum(ssl, *ssl->argv, *ssl->argv, 0);
				ssl->argv++;
			}
		}
		else
			ssl_file_print(ssl, tmp);
	}
}

void					digest_verify(t_ssl *const ssl, char **argv)
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
					!*argv ? exit_nostring(ssl, 's') : argv++;
			}
			else
				exit_flags(ssl, *tmp);
		}
	}
	if (!*argv && !(ssl->flags & FLAGS_P) && !(ssl->flags & FLAGS_S))
		read_stdin_print(ssl);
}
