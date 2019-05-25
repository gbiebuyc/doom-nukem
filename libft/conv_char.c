/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 20:45:33 by mikorale          #+#    #+#             */
/*   Updated: 2018/10/23 18:10:16 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	conv_wchar(va_list ap, t_f_id *id, char zero_space)
{
	wint_t	wc;
	int		count;
	int		len_byte;

	count = 0;
	wc = va_arg(ap, wint_t);
	len_byte = my_wcharlen(wc);
	if ((wc >= 0xD800 && wc <= 0xDFFF) || wc > 0x10FFFF || wc < 0
			|| (MB_CUR_MAX < 2 && wc > 255))
		return (id->error = -1);
	if (id->field > 1 && !id->flag->hyphen)
		count += write_n(zero_space, id->field - len_byte);
	count += my_putwchar(wc);
	if (id->field > 1 && id->flag->hyphen)
		count += write_n(zero_space, id->field - len_byte);
	fflush(stdout);
	return (count);
}

int			conv_char(const char *format, va_list ap, t_f_id *id)
{
	int		count;
	int		c;
	char	zero_space;

	get_flags(format, id);
	get_field_n_preci(format + id->i, id);
	get_modifier(format, id);
	zero_space = (id->flag->zero) ? '0' : ' ';
	if (id->modifier[0] && (MB_CUR_MAX > 1))
		return (conv_wchar(ap, id, zero_space));
	count = 0;
	c = (id->invalid == 0) ? va_arg(ap, int) : id->conv_type;
	if (c > 255)
		return (id->error = -1);
	if (!id->flag->hyphen && id->field > 1)
		count += write_n(zero_space, id->field - 1);
	count += ft_fputc(c, stdout);
	if (id->flag->hyphen && id->field > 1)
		count += write_n(' ', id->field - 1);
	fflush(stdout);
	return (count);
}
