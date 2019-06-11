/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_non_printable_str.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 17:03:50 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/18 23:14:48 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		non_printable_char(unsigned char c, bool do_print, int fd)
{
	char	*res;

	if (ft_isprint(c))
		res = (char[]){c, '\0'};
	else if (c == '\t')
		res = "\\t";
	else if (c == '\v')
		res = "\\v";
	else if (c == '\n')
		res = "\\n";
	else if (c == '\r')
		res = "\\r";
	else if (c == '\f')
		res = "\\f";
	else
		res = (char[]){'\\', '0' + (c / 16), '0' + (c % 16)};
	if (do_print)
		ft_putstr_fd(res, fd);
	return (ft_strlen(res));
}

void	non_printable_str_conv(char *s, t_data *d)
{
	int	len;
	int	padding_len;
	int	i;

	if (!s)
		s = "(null)";
	i = 0;
	len = 0;
	while (s[i] && (d->precision == -1 ||
				(len + non_printable_char(s[i], false, 0) <= d->precision)))
		len += non_printable_char(s[i++], false, 0);
	padding_len = ft_max(0, d->field_width - len);
	*(d->print_count) += padding_len + len;
	while (!d->left_ajusted && padding_len-- > 0)
		ft_putchar_fd((d->zero_padding) ? '0' : ' ', d->fd);
	while (*s && len > 0)
		len -= non_printable_char(*s++, true, d->fd);
	while (d->left_ajusted && padding_len-- > 0)
		ft_putchar_fd(' ', d->fd);
}
