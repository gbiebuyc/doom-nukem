/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_signed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:51:40 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/18 23:14:48 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	diuoxb_padding_and_print(t_data *d)
{
	int		padding_len;
	char	padding_char;

	padding_len = ft_max(0, d->field_width - d->conv_len - d->prefix_len);
	padding_char = (d->zero_padding &&
			!d->left_ajusted && d->precision < 0) ? '0' : ' ';
	(*d->print_count) += padding_len + d->conv_len + d->prefix_len;
	while (padding_char == ' ' && !d->left_ajusted && padding_len-- > 0)
		ft_putchar_fd(' ', d->fd);
	ft_putstrn_fd(d->fd, d->prefix, d->prefix_len);
	while (padding_char == '0' && !d->left_ajusted && padding_len-- > 0)
		ft_putchar_fd('0', d->fd);
	ft_putstrn_fd(d->fd, d->converted, d->conv_len);
	while (d->left_ajusted && padding_len-- > 0)
		ft_putchar_fd(' ', d->fd);
}

void	get_sign(bool is_neg, t_data *d)
{
	if (is_neg)
		ft_strncpy(d->prefix, "-", (d->prefix_len = 1));
	else if (d->show_plus_sign)
		ft_strncpy(d->prefix, "+", (d->prefix_len = 1));
	else if (d->space_before_positive_num)
		ft_strncpy(d->prefix, " ", (d->prefix_len = 1));
}

void	di_conv(intmax_t n, t_data *d)
{
	intmax_t	n2;
	int			len;

	get_sign((n < 0), d);
	if (n == (-9223372036854775807LL - 1LL))
		ft_strncpy(d->converted, "9223372036854775808", (d->conv_len = 19));
	else
	{
		n = (n < 0) ? -n : n;
		n2 = n;
		len = 0;
		while (n2 && ++len)
			n2 /= 10;
		len = (d->precision == -1 && len < 1) ? 1 : len;
		len = (d->precision > len) ? d->precision : len;
		d->conv_len = len;
		d->converted[len] = '\0';
		while (--len >= 0)
		{
			d->converted[len] = n % 10 + '0';
			n /= 10;
		}
	}
	diuoxb_padding_and_print(d);
}
