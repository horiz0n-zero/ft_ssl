/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cypher_des_verify_execute.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:00:56 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/15 14:31:25 by afeuerst         ###   ########.fr       */
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

static void			des_io(t_ssl *const ssl, const char *const file,
		const int state)
{
	int				fd;

	if (state & FLAGS_I)
		fd = open(file, O_RDONLY);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC,
				S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (fd < -1)
		error_file(ssl, file);
	if (state & FLAGS_I)
	{
		if (ssl->stdin != STDIN_FILENO)
			close(ssl->stdin);
		ssl->stdin = fd;
		ssl->stdin_file = file;
	}
	else
	{
		if (ssl->stdout != STDOUT_FILENO)
			close(ssl->stdout);
		ssl->stdout = fd;
	}
}

static void			execute(t_ssl *const ssl, t_des *const des)
{
	void			*ptr;
	void			*result;

	if (!(ssl->flags & FLAGS_K))
		des_pbkdf(des, des->password, des->salt);
	else if (!(ssl->flags & FLAGS_V) && ssl->algo->settings & CBC)
		exit_custom("ft_ssl: Error: you must provide IV.\n");
	if (ssl->stdin == STDIN_FILENO)
		ptr = read_stdin(ssl);
	else
		ptr = ssl_input(ssl, ssl->stdin_file, ssl->stdin);
	result = ssl->algo->checksum(ssl, ptr, ssl->source_lenght);
	write(ssl->stdout, result, ssl->source_lenght);
	free(result);
	free(ptr);
	if (ssl->stdin != STDIN_FILENO)
		close(ssl->stdin);
	if (ssl->stdout != STDOUT_FILENO)
		close(ssl->stdout);
}

void				des_execute(t_ssl *const ssl, int c_flags)
{
	t_des			des;
	int				state;

	ssl->required = &des;
	while (*ssl->argv && **ssl->argv == '-')
	{
		state = g_available_flags[(int)*((*ssl->argv++) + 1)];
		if (state & (FLAGS_I | FLAGS_O))
			des_io(ssl, *ssl->argv++, state);
		else if (state & FLAGS_P)
			des.password = *ssl->argv++;
		else if (state & FLAGS_K)
			des_hexa(*ssl->argv++, &des.key);
		else if (state & FLAGS_S)
			des_hexa(*ssl->argv++, &des.salt);
		else if (state & FLAGS_V)
			des_hexa(*ssl->argv++, &des.vector);
	}
	if (!(ssl->flags & FLAGS_S))
		des.salt = des_randomkey();
	if (!(ssl->flags & (FLAGS_P | FLAGS_K)))
		des.password = des_getpass(ssl);
	execute(ssl, &des);
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
