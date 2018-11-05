/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 14:32:55 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/05 16:45:21 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/stat.h>

typedef struct s_ssl			t_ssl;

typedef struct					s_algo
{
	char						*(*checksum)(const char *const src, const size_t len);
	const char					*algo;
	int							type;
# define TYPE_STANDARD 1
# define TYPE_DIGEST 2
# define TYPE_CIPHER 4

	int							pad;
	void						(*verify)(t_ssl *const ssl, char **argv);
	void						(*execute)(t_ssl *const ssl, int cflags); // cflags for norme
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
# define FLAGS_D 16
# define FLAGS_E 32
# define FLAGS_I 64
# define FLAGS_O 128
# define STATE_FILE 1

	const struct s_algo			*algo;
	size_t						source_lenght;
}								t_ssl;

void							ssl_get_algo(t_ssl *const ssl,
		const char *const type);


char							*algo_md5(const char *const src, const size_t len);
char							*algo_sha256(const char *const src, const size_t len);

void							digest_execute(t_ssl *const ssl, int c_flags);
void							digest_verify(t_ssl *const ssl, char **argv);
void							base64_execute(t_ssl *const ssl, int c_flags);
void							base64_verify(t_ssl *const ssl, char **argv);

void							print_checksum(t_ssl *const ssl,
		const char *const src, const char *const name, const int isflagsp);
void							read_stdin(t_ssl *const ssl);

void							exit_flags(t_ssl *const ssl, const char c);
void							exit_nostring(t_ssl *const ssl, const char c);
void							exit_badcombination(t_ssl *const ssl);

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
