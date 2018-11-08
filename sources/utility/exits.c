/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 15:05:16 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/08 16:05:19 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static const char			*g_usages[] =
{
	"usage: { md5 sha256 } [-pqr] [-s string] [files ...]\n",
	"usage: base64 [-de] [-i input file] [-o output file]\n",
	"usage: { des des-ecb des-cbc } [-ade] [-i input file] [-o output file] \
	[-k key] [-p password] [-s salt] [-v vector]\n"
};

void						usage(t_ssl *const ssl)
{
	if (ssl->algo->type & TYPE_DIGEST)
		ft_fprintf(STDERR_FILENO, g_usages[0]);
	else if (ssl->algo->execute == base64_execute)
		ft_fprintf(STDERR_FILENO, g_usages[1]);
	else if (ssl->algo->type & TYPE_CIPHER)
		ft_fprintf(STDERR_FILENO, g_usages[2]);
	exit(EXIT_FAILURE);
}

void						exit_flags(t_ssl *const ssl, const char c)
{
	ft_fprintf(STDERR_FILENO, "ft_ssl: illegal option -- %c\n", c);
	usage(ssl);
}

void						exit_badcombination(t_ssl *const ssl)
{
	ft_fprintf(STDERR_FILENO, "ft_ssl: error: bad flags combination\n");
	usage(ssl);
}

void						exit_nostring(t_ssl *const ssl, const char c)
{
	ft_fprintf(STDERR_FILENO, "ft_ssl: option requires an argument -- %c\n",
			c);
	usage(ssl);
}
