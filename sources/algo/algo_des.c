/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_des.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afeuerst <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:11:40 by afeuerst          #+#    #+#             */
/*   Updated: 2018/11/08 17:41:38 by afeuerst         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"

char						*algo_des(t_ssl *const ssl, const char *const src,
		const size_t len)
{
	struct s_des *const		des = ssl->required;

	(void)des;
	return ("des");
}
