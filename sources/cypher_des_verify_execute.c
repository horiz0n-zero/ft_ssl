/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cypher_des_verify_execute.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:00:56 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/08 14:05:36 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

static const int	g_available_flags[256] =
{
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
	
}

void				des_verify(t_ssl *const ssl, char **argv)
{
	ft_printf("password is %s\n", des_getpass(ssl));
}












