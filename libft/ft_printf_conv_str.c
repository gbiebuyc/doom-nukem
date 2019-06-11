/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 17:01:32 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/18 23:14:48 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	s_conv(char *s, t_data *d)
{
	int len;
	int	padding_len;

	if (!s)
		s = "(null)";
	len = ft_strlen(s);
	if (d->precision >= 0 && d->precision < len)
		len = d->precision;
	padding_len = ft_max(0, d->field_width - len);
	*(d->print_count) += padding_len + len;
	while (!d->left_ajusted && padding_len-- > 0)
		ft_putchar_fd((d->zero_padding) ? '0' : ' ', d->fd);
	ft_putstrn_fd(d->fd, s, len);
	while (d->left_ajusted && padding_len-- > 0)
		ft_putchar_fd(' ', d->fd);
}

void	wstr_conv(wchar_t *s, t_data *d)
{
	int len;
	int	padding_len;
	int i;

	if (!s)
		s = L"(null)";
	i = 0;
	len = 0;
	while (s[i] && (d->precision == -1 ||
				(len + ft_wcharlen(s[i]) <= d->precision)))
		len += ft_wcharlen(s[i++]);
	padding_len = ft_max(0, d->field_width - len);
	*(d->print_count) += padding_len + len;
	while (!d->left_ajusted && padding_len-- > 0)
		ft_putchar_fd((d->zero_padding) ? '0' : ' ', d->fd);
	while (*s && len > 0)
	{
		ft_putwchar_fd(*s, d->fd);
		len -= ft_wcharlen(*s);
		s++;
	}
	while (d->left_ajusted && padding_len-- > 0)
		ft_putchar_fd(' ', d->fd);
}
