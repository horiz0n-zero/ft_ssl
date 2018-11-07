/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_get_algo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 10:48:56 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/06 13:34:32 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static const struct s_algo	g_algos[] =
{
	{algo_md5, "MD5", TYPE_DIGEST, 0, digest_verify, digest_execute},
	{algo_sha256, "SHA256", TYPE_DIGEST, 0, digest_verify, digest_execute},
	{algo_base64, "BASE64", TYPE_CIPHER, 0, base64_verify, base64_execute},
	{algo_md5, "DES", TYPE_CIPHER, 0, NULL, NULL},
	{algo_md5, "DES-ECB", TYPE_CIPHER, 0, NULL, NULL},
	{algo_md5, "DES-CBC", TYPE_CIPHER, 0, NULL, NULL}
};

static inline void			print_digest(const int type)
{
	int						index;
	static const int		count = (int)(sizeof(g_algos) / sizeof(t_algo));

	index = 0;
	while (index < count)
	{
		if (g_algos[index].type != type)
		{
			index++;
			continue;
		}
		ft_fprintf(STDERR_FILENO, "%s\n", g_algos[index].algo);
		index++;
	}
}

static inline void			ssl_no_algo(const char *const type)
{
	ft_fprintf(STDERR_FILENO, "ft_ssl: Error: ");
	if (!type)
		ft_fprintf(STDERR_FILENO, "no command provided.\n");
	else
	{
		ft_fprintf(STDERR_FILENO, "\'%s\' is an invalid command.\n",
				type);
	}
	ft_fprintf(STDERR_FILENO, "\nStandard commands:\n");
	print_digest(TYPE_STANDARD);
	ft_fprintf(STDERR_FILENO, "\nMessage Digest commands:\n");
	print_digest(TYPE_DIGEST);
	ft_fprintf(STDERR_FILENO, "\nCipher commands:\n");
	print_digest(TYPE_CIPHER);
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
