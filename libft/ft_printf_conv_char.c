/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:59:14 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/18 23:14:48 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	c_conv(char c, t_data *d)
{
	int padding_len;

	padding_len = ft_max(0, d->field_width - 1);
	*(d->print_count) += padding_len + 1;
	while (!d->left_ajusted && padding_len-- > 0)
		ft_putchar_fd((d->zero_padding) ? '0' : ' ', d->fd);
	ft_putchar_fd(c, d->fd);
	while (d->left_ajusted && padding_len-- > 0)
		ft_putchar_fd(' ', d->fd);
}

void	wchar_conv(wchar_t c, t_data *d)
{
	int padding_len;

	padding_len = ft_max(0, d->field_width - ft_wcharlen(c));
	*(d->print_count) += padding_len + ft_wcharlen(c);
	while (!d->left_ajusted && padding_len-- > 0)
		ft_putchar_fd((d->zero_padding) ? '0' : ' ', d->fd);
	ft_putwchar_fd(c, d->fd);
	while (d->left_ajusted && padding_len-- > 0)
		ft_putchar_fd(' ', d->fd);
}
