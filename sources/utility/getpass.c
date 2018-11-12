/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpass.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:45:56 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/08 14:42:57 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char				*des_getpass(void)
{
	char			*pass;
	char			*conf;

	if (ssl->algo->settings & ECB)
		pass = getpass("enter des-ecb encryption password:");
	else
		pass = getpass("enter des-cbc encryption password:");
	pass = ft_strndup(pass, ft_strlen(pass));
	if (ssl->algo->settings & ECB)
		conf = getpass("Verifying - enter des-ecb encryption password:");
	else
		conf = getpass("Verifying - enter des-cbc encryption password:");
	if (ft_strcmp(pass, conf))
	{
		ft_printf("Verify failure\n");
		free(pass);
		return (des_getpass());
	}
	return (pass);
}
