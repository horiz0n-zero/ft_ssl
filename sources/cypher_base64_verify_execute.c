/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cypher_base64_verify_execute.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 09:55:52 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/08 11:01:39 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64.h"

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
};

void				base64_execute(t_ssl *const ssl, int c_flags)
{
	void			*ptr;
	void			*result;

	if (ssl->stdin == STDIN_FILENO)
		ptr = read_stdin(ssl);
	else
		ptr = ssl_input(ssl, ssl->stdin_file, ssl->stdin);
	if (!ptr)
		return ;
	result = ssl->algo->checksum(ssl, ptr, ssl->source_lenght);
	write(ssl->stdout, result, ft_strlen(result));
	free(ptr);
	if (ft_strcmp(result, INVALID))
		free(result);
	if (ssl->stdout != STDOUT_FILENO)
		close(ssl->stdout);
	if (ssl->stdin != STDIN_FILENO)
		close(ssl->stdin);
}

static inline void	base64_io(t_ssl *const ssl, const char *const file,
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

void				base64_verify(t_ssl *const ssl, char **argv)
{
	char			*tmp;
	int				state;

	ssl->stdin = STDIN_FILENO;
	ssl->stdout = STDOUT_FILENO;
	while (*argv && **argv == '-' && (tmp = *argv++))
	{
		while (*++tmp)
		{
			state = g_available_flags[(int)*tmp];
			if ((ssl->flags |= state) && state & (FLAGS_I | FLAGS_O))
			{
				if (!*argv)
					exit_nostring(ssl, *tmp);
				else
					base64_io(ssl, *argv++, state);
				break ;
			}
		}
	}
	if (ssl->flags & FLAGS_E && ssl->flags & FLAGS_D)
		exit_badcombination(ssl);
}
