/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_unsigned.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:56:44 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/18 23:14:48 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_prefix(t_data *d)
{
	if (d->base_len == 8 && d->converted[0] != '0')
		ft_strncpy(d->prefix, "0", (d->prefix_len = 1));
	else if (d->base_len == 16 && d->base[10] == 'a')
		ft_strncpy(d->prefix, "0x", (d->prefix_len = 2));
	else if (d->base_len == 16 && d->base[10] == 'A')
		ft_strncpy(d->prefix, "0X", (d->prefix_len = 2));
}

void	get_base(char c, t_data *d)
{
	if (c == 'o')
		ft_strncpy(d->base, "01234567", (d->base_len = 8));
	else if (c == 'x' || c == 'p')
		ft_strncpy(d->base, "0123456789abcdef", (d->base_len = 16));
	else if (c == 'X')
		ft_strncpy(d->base, "0123456789ABCDEF", (d->base_len = 16));
	else
		ft_strncpy(d->base, "0123456789", (d->base_len = 10));
}

void	uoxb_conv(uintmax_t n, char c, t_data *d)
{
	uintmax_t	n2;
	int			len;

	get_base(c, d);
	if (c == 'p')
		d->alternate_form = true;
	else if ((c == 'x' || c == 'X') && n == 0)
		d->alternate_form = false;
	n2 = n;
	len = 0;
	while (n2 && ++len)
		n2 /= d->base_len;
	len = (d->precision == -1 && len < 1) ? 1 : len;
	len = (d->precision > len) ? d->precision : len;
	d->conv_len = len;
	d->converted[len] = '\0';
	while (--len >= 0)
	{
		d->converted[len] = d->base[n % d->base_len];
		n /= d->base_len;
	}
	if (d->alternate_form)
		get_prefix(d);
	diuoxb_padding_and_print(d);
}
