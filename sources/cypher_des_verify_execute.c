/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cypher_des_verify_execute.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:00:56 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/08 17:42:58 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

static const int	g_available_flags[256] =
{
	['a'] = FLAGS_A,
	['A'] = FLAGS_A,
	['d'] = FLAGS_D,
	['D'] = FLAGS_D,
	['e'] = FLAGS_E,
	['E'] = FLAGS_E,
	['i'] = FLAGS_I,
	['I'] = FLAGS_I,
	['o'] = FLAGS_O,
	['O'] = FLAGS_O,
	['k'] = FLAGS_K,
	['K'] = FLAGS_K,
	['p'] = FLAGS_P,
	['P'] = FLAGS_P,
	['s'] = FLAGS_S,
	['S'] = FLAGS_S,
	['v'] = FLAGS_V,
	['V'] = FLAGS_V
};

void				des_execute(t_ssl *const ssl, int c_flags)
{
	t_des			des;

	ssl->required = &des;
}

void				des_verify(t_ssl *const ssl, char **argv)
{
	int				state;
	char			*tmp;

	ssl->stdout = STDOUT_FILENO;
	ssl->stdin = STDIN_FILENO;
	while (*argv && **argv == '-' && (tmp = *argv++))
	{
		state = g_available_flags[(int)*++tmp];
		ssl->flags |= state;
		if (!state)
			exit_flags_string(ssl, tmp - 1);
		else if (*(tmp + 1))
			exit_flags_string(ssl, tmp - 1);
		else if ((state & (FLAGS_I | FLAGS_O | FLAGS_P)) && !*argv++)
			exit_nostring(ssl, *tmp);
		else if (state & (FLAGS_K | FLAGS_S | FLAGS_V))
		{
			if (!*argv)
				exit_nostring(ssl, *tmp);
			else
				exit_nonhexa(ssl, *argv++, *tmp);
		}
	}
	if (ssl->flags & FLAGS_E && ssl->flags & FLAGS_D)
		exit_badcombination(ssl);
}
