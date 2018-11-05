/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 14:32:40 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/05 16:53:42 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int						main(int argc, char **argv)
{
	t_ssl				ssl;

	(void)argc;
	ssl.argv = ++argv;
	ssl.flags = 0;
	ssl.algo = NULL;
	ssl_get_algo(&ssl, *argv++);
	ssl.algo->verify(&ssl, argv);
	ssl.algo->execute(&ssl, 0);
	return (EXIT_SUCCESS);
}
