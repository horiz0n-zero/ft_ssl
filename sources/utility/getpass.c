/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpass.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:45:56 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/23 11:03:18 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

void				des_pbkdf(t_des *const des,
		const void *const pass, uint64_t salt)
{
	const size_t	len = ft_strlen(pass);
	const size_t	total_len = len + sizeof(uint64_t);
	char			*stack_buffer;
	char			*result;

	salt = __builtin_bswap64(salt);
	stack_buffer = __builtin_alloca(total_len);
	ft_memcpy(stack_buffer, pass, len);
	ft_memcpy(stack_buffer + len, &salt, sizeof(uint64_t));
	result = algo_md5(NULL, stack_buffer, total_len);
	des->vector = ft_hexa_binary(result + 16);
	result[16] = 0;
	des->key = ft_hexa_binary(result);
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
