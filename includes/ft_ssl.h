/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 14:32:55 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/15 10:40:18 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>
# include "libprintf.h"

typedef struct s_ssl			t_ssl;

typedef struct					s_algo
{
	char						*(*checksum)(t_ssl *const ssl,
			const char *const src, const size_t len);
	const char					*algo;
	int							type;
# define TYPE_STANDARD 1
# define TYPE_DIGEST 2
# define TYPE_CIPHER 4

	int							settings;
# define ECB 1
# define CBC 2

	void						(*verify)(t_ssl *const ssl, char **argv);
	void						(*execute)(t_ssl *const ssl, int cflags);
}								t_algo;

struct							s_ssl
{
	char						**argv;
	int							flags;
# define FLAGS_P 1
# define FLAGS_Q 2
# define FLAGS_R 4
# define FLAGS_S 8
# define FLAGS_D 16
# define FLAGS_E 32
# define FLAGS_I 64
# define FLAGS_O 128
# define FLAGS_K 256
# define FLAGS_V 512
# define FLAGS_A 1024
# define STATE_FILE 1

	int							settings;
	const struct s_algo			*algo;
	size_t						source_lenght;
	int							stdin;
	const char					*stdin_file;
	int							stdout;
	void						*required;
};

void							ssl_get_algo(t_ssl *const ssl,
		const char *const type);

char							*algo_md5(t_ssl *const ssl,
		const char *const src, const size_t len);
void							*algo_md5_raw(const char *const src,
		const size_t len);
char							*algo_sha256(t_ssl *const ssl,
		const char *const src, const size_t len);
char							*algo_base64(t_ssl *const ssl,
		const char *const src, const size_t len);
char							*algo_des(t_ssl *const ssl,
		const char *const src, const size_t len);

void							digest_execute(t_ssl *const ssl, int c_flags);
void							digest_verify(t_ssl *const ssl, char **argv);
void							base64_execute(t_ssl *const ssl, int c_flags);
void							base64_verify(t_ssl *const ssl, char **argv);
void							des_verify(t_ssl *const ssl, char **argv);
void							des_execute(t_ssl *const ssl, int c_flags);

void							print_checksum(t_ssl *const ssl,
		const char *const src, const char *const name, const int isflagsp);
void							read_stdin_print(t_ssl *const ssl);
void							*read_stdin(t_ssl *const ssl);

void							exit_flags(t_ssl *const ssl, const char c);
void							exit_flags_string(t_ssl *const ssl,
		const char *const src);
void							exit_nostring(t_ssl *const ssl, const char c);
void							exit_badcombination(t_ssl *const ssl);
void							exit_nonhexa(t_ssl *const ssl, const char *src,
		const char c);

void							exit_custom(const char *const err);
void							usage(t_ssl *const ssl);
void							error_file(t_ssl *const ssl,
		const char *const file);
void							*error_file_null(t_ssl *const ssl,
		const char *const file);
char							*lstrjoin(const char *s1, size_t l1,
		const char *s2, size_t l2);
char							*ft_strndup(const char *const src,
		const size_t len);
int								ft_strcomparable(const char *src,
		const char *compare);
size_t							ft_strlen(const char *const src);
int								ft_strcmp(register const char *s1,
		register const char *s2);
void							ft_memcpy(void *dst, const void *src, size_t n);
void							ft_memset(char *dst, unsigned long len);
void							ssl_input_print(t_ssl *const ssl,
		const char *const file, const int fd);
void							ssl_file_print(t_ssl *const ssl,
		const char *const file);
void							*ssl_input(t_ssl *const ssl,
		const char *const file, const int fd);
void							*ssl_file(t_ssl *const ssl,
		const char *const file);
char							*des_getpass(t_ssl *const ssl);
uint64_t						des_randomkey(void);
void							des_hexa(const char *src,
		uint64_t *const value);

#endif
