/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_percent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 18:28:06 by mikorale          #+#    #+#             */
/*   Updated: 2018/10/23 17:55:24 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		conv_percent(const char *format, va_list ap, t_f_id *id)
{
	int		count;
	char	zero_space;

	(void)ap;
	get_flags(format + 1, id);
	get_field_n_preci(format + 1 + id->i, id);
	zero_space = (id->flag->zero) ? '0' : ' ';
	count = 0;
	if (!id->flag->hyphen && id->field > 1)
		count += write_n(zero_space, id->field - 1);
	count += ft_fputc('%', stdout);
	if (id->flag->hyphen && id->field > 1)
		count += write_n(' ', id->field - 1);
	fflush(stdout);
	return (count);
}
