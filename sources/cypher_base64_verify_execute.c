/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cypher_base64_verify_execute.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 09:55:52 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/05 16:36:37 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static const int		g_available_flags[256] =
{
	['d'] = FLAGS_D,
	['D'] = FLAGS_D,
	['e'] = FLAGS_E,
	['E'] = FLAGS_E,
	['i'] = FLAGS_I,
	['I'] = FLAGS_I,
	['o'] = FLAGS_O,
	['O'] = FLAGS_O
};

void					base64_execute(t_ssl *const ssl, int c_flags)
{
	
}

void					base64_verify(t_ssl *const ssl, char **argv)
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
				if (g_available_flags[(int)*tmp++] & (FLAGS_I | FLAGS_O))
					!*argv ? exit_nostring(ssl, *(tmp - 1)) : argv++;
			}
			else
				exit_flags(ssl, *tmp);
		}
	}
	if (ssl->flags & FLAGS_E && ssl->flags & FLAGS_D)
		exit_badcombination(ssl);
	// default read stdin ???
}
