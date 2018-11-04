/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_get_algo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 10:48:56 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/01 10:38:55 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static const struct s_algo	g_algos[] =
{
	{algo_md5, "MD5"},
	{algo_sha256, "SHA256"}
};

static inline void			print_digest(void)
{
	int						index;
	static const int		count = (int)(sizeof(g_algos) / sizeof(t_algo));

	index = 0;
	while (index < count)
	{
		write(STDERR_FILENO, g_algos[index].algo,
				ft_strlen(g_algos[index].algo));
		write(STDERR_FILENO, "\n", 1);
		index++;
	}
}

static inline void			ssl_no_algo(const char *const type)
{
	write(STDERR_FILENO, "ft_ssl: Error: ",
			sizeof("ft_ssl: Error: "));
	if (!type)
		write(STDERR_FILENO, "no command provided.\n",
				sizeof("no command provided.\n"));
	else
	{
		write(STDERR_FILENO, "\'", 1);
		write(STDERR_FILENO, type, ft_strlen(type));
		write(STDERR_FILENO, "\'", 1);
		write(STDERR_FILENO, " is an invalid command.\n",
				sizeof(" is an invalid command.\n"));
	}
	write(STDERR_FILENO, "\nStandard commands:\n",
			sizeof("\nStandard commands:\n"));
	write(STDERR_FILENO, "\nMessage Digest commands:\n",
			sizeof("\nMessage Digest commands:\n"));
	print_digest();
	write(STDERR_FILENO, "\nCipher commands:\n",
			sizeof("\nCipher commands:\n"));
	exit(EXIT_FAILURE);
}

void						ssl_get_algo(t_ssl *const ssl,
		const char *const type)
{
	static const int		count = (int)(sizeof(g_algos) / sizeof(t_algo));
	int						index;
	const t_algo			*ptr;

	if (!type)
		return (ssl_no_algo(type));
	index = 0;
	while (index < count)
	{
		ptr = g_algos + index++;
		if (!ft_strcomparable(type, ptr->algo))
		{
			ssl->algo = ptr;
			break ;
		}
	}
	if (!ssl->algo)
		return (ssl_no_algo(type));
	ssl->argv++;
}
