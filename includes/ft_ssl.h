/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 14:32:55 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/01 10:34:47 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>

typedef struct					s_algo
{
	char						*(*checksum)(const char *src);
	const char					*algo;
}								t_algo;

typedef struct					s_ssl
{
	char						**argv;
	int							flags;
	int							pad;
# define FLAGS_P 1
# define FLAGS_Q 2
# define FLAGS_R 4
# define FLAGS_S 8
# define STATE_FILE 1

	const struct s_algo			*algo;
}								t_ssl;

void							ssl_get_algo(t_ssl *const ssl,
		const char *const type);
char							*algo_md5(const char *const src);
char							*algo_sha256(const char *const src);
void							print_checksum(t_ssl *const ssl,
		const char *const src, const char *const name, const int isflagsp);
void							read_stdin(t_ssl *const ssl);

void							exit_flags(t_ssl *const ssl, const char c);
void							exit_nostring(t_ssl *const ssl);
void							usage(t_ssl *const ssl);
void							error_file(t_ssl *const ssl,
		const char *const file);
char							*ft_strjoin(const char *s1,
		const char *s2);
char							*ft_strndup(const char *const src,
		const size_t len);
int								ft_strcomparable(const char *src,
		const char *compare);
size_t							ft_strlen(const char *const src);
int								ft_strcmp(register const char *s1,
		register const char *s2);
void							ft_memcpy(void *dst, const void *src, size_t n);
void							ft_memset(char *dst, unsigned long len);

#endif
