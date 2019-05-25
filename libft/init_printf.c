/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 19:01:42 by mikorale          #+#    #+#             */
/*   Updated: 2018/10/23 13:41:35 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_conv_list(void)
{
	g_conv_list[0] = &conv_char;
	g_conv_list[1] = &conv_char;
	g_conv_list[2] = &conv_int;
	g_conv_list[3] = &conv_int;
	g_conv_list[4] = &conv_int;
	g_conv_list[5] = &conv_int;
	g_conv_list[6] = &conv_int;
	g_conv_list[7] = &conv_int;
	g_conv_list[8] = &conv_string;
	g_conv_list[9] = &conv_string;
	g_conv_list[10] = &conv_int;
	g_conv_list[11] = &conv_int;
	g_conv_list[12] = &conv_int;
	g_conv_list[13] = &conv_int;
	g_conv_list[14] = &conv_percent;
}

/*
** You really need a comment to understand this ?
*/

void	init(t_f_id *id)
{
	id->flag->hyphen = 0;
	id->flag->plus = 0;
	id->flag->hash = 0;
	id->flag->zero = 0;
	id->flag->blank = 0;
	id->preci = -1;
	id->field = 0;
	id->period = 0;
	id->arg_int = 0;
	id->arg_uint = 0;
	id->modifier[0] = 0;
	id->modifier[1] = 0;
	id->modifier[2] = 0;
	id->modifier[3] = 0;
	id->modifier[4] = 0;
	id->modifier[5] = 0;
	id->i = 0;
	id->base = 0;
	id->invalid = 0;
}
