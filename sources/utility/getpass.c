/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpass.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:45:56 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/19 15:28:01 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

void				des_pbkdf(t_des *const des,
		const void *const pass, uint64_t salt)
{
	const size_t	len = ft_strlen(pass);
	char			*buffer;
	uint64_t		*result;

	buffer = __builtin_alloca(len + sizeof(uint64_t));
	ft_memcpy(buffer, pass, len);
	ft_memcpy(buffer + len, &salt, sizeof(uint64_t));
	result = algo_md5_raw(buffer, len + sizeof(uint64_t));
	des->key = *result++;
	des->vector = *result;
}

uint64_t			des_randomkey(void)
{
	static uint64_t	failure = 0xf42f23ab87dd43af;
	uint64_t		value;
	const int		fd = open("/dev/urandom", O_RDONLY);

	if (fd < 0)
	{
		value = failure;
		failure = ((failure << 2 | (failure >> (64 - 2))));
	}
	else
		read(fd, &value, sizeof(uint64_t));
	close(fd);
	return (value);
}

char				*des_getpass(t_ssl *const ssl)
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
		return (des_getpass(ssl));
	}
	return (pass);
}
