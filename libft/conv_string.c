/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 20:44:28 by mikorale          #+#    #+#             */
/*   Updated: 2018/10/23 18:14:12 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	conv_wstring(va_list ap, t_f_id *id)
{
	wchar_t	*wstr;
	size_t	len;
	int		count;
	char	zero_space;

	zero_space = (id->flag->zero) ? '0' : ' ';
	count = 0;
	if ((wstr = va_arg(ap, wchar_t *)) == NULL)
		wstr = L"(null)";
	len = my_wstrlen(wstr);
	id->preci = (int)get_wpreci(wstr, id->preci, 0);
	if (id->preci < 0)
		id->preci = (int)len;
	id->preci = (id->preci > (int)len) ? len : id->preci;
	len = (id->period) ? id->preci : len;
	if (id->field > 0 && !id->flag->hyphen)
		count += write_n(zero_space, id->field - len);
	count += my_putwstr(wstr, len);
	if (id->field > 0 && id->flag->hyphen)
		count += write_n(' ', id->field - len);
	return (count);
}

int			conv_string(const char *format, va_list ap, t_f_id *id)
{
	size_t	len;
	int		count;

	count = 0;
	get_flags(format, id);
	get_field_n_preci(format + id->i, id);
	get_modifier(format, id);
	if (id->modifier[0] && MB_CUR_MAX > 1)
		return (conv_wstring(ap, id));
	if ((id->conv_res = va_arg(ap, char*)) == NULL)
		id->conv_res = "(null)";
	len = my_strlen(id->conv_res);
	if (id->preci == -1)
		id->preci = INT_MAX;
	if (id->preci > (int)len)
		id->preci = len;
	count += print(id->preci, id);
	return (count);
}
