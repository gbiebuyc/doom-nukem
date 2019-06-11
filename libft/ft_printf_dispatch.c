/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 10:15:01 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/18 23:14:48 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	convert2(char **s, t_data *d, va_list valist)
{
	if (**s == 'f')
		float128_conv(get_float(d, valist), 0, d);
	else if (**s == 'F')
		float128_conv(get_float(d, valist), 1, d);
	else if ((**s == 'c' && d->len_mod == 3) || **s == 'C')
		wchar_conv(va_arg(valist, wchar_t), d);
	else if ((**s == 's' && d->len_mod == 3) || **s == 'S')
		wstr_conv(va_arg(valist, wchar_t*), d);
	else if (**s == 'c')
		c_conv((char)va_arg(valist, int), d);
	else if (**s == 's')
		s_conv(va_arg(valist, char*), d);
	else if (**s == 'b' && d->len_mod == 3)
		print_bits(va_arg(valist, uint64_t), 64, d);
	else if (**s == 'b')
		print_bits(va_arg(valist, uint32_t), 32, d);
	else if (**s == 'k')
		print_iso8601_date(va_arg(valist, int32_t), d);
	else if (**s == 'r')
		non_printable_str_conv(va_arg(valist, char*), d);
	else if (**s)
		c_conv(**s, d);
	else
		return ;
	(*s)++;
}

void	convert(char **s, t_data *d, va_list valist)
{
	if (**s == '%')
		c_conv('%', d);
	else if (**s == 'd' || **s == 'i')
		di_conv(get_signed(d, valist), d);
	else if (**s == 'u' || **s == 'o' || **s == 'x' || **s == 'X')
		uoxb_conv(get_unsigned(d, valist), **s, d);
	else if (**s == 'p')
		uoxb_conv((uintmax_t)va_arg(valist, void*), **s, d);
	else if (**s == 'D')
		di_conv(va_arg(valist, long int), d);
	else if (**s == 'O')
		uoxb_conv(va_arg(valist, unsigned long int), 'o', d);
	else if (**s == 'U')
		uoxb_conv(va_arg(valist, unsigned long int), 'u', d);
	else
		return (convert2(s, d, valist));
	(*s)++;
}
