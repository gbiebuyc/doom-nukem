/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_misc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 17:29:21 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/18 23:14:48 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_bits(uintmax_t bits, int shift, t_data *d)
{
	int	i;

	i = 0;
	while (--shift >= 0)
		d->converted[i++] = (bits & ((uintmax_t)1 << shift)) ? '1' : '0';
	d->converted[i] = '\0';
	s_conv(d->converted, d);
}

/*
** The positive int date argument in the form YYYYMMDD
** is converted to ISO 8601 date representation.
** If date is negative, the result is undefined.
*/

void	print_iso8601_date(int32_t date, t_data *d)
{
	d->converted[10] = '\0';
	d->converted[9] = '0' + date % 10;
	d->converted[8] = '0' + (date /= 10) % 10;
	d->converted[7] = '-';
	d->converted[6] = '0' + (date /= 10) % 10;
	d->converted[5] = '0' + (date /= 10) % 10;
	d->converted[4] = '-';
	d->converted[3] = '0' + (date /= 10) % 10;
	d->converted[2] = '0' + (date /= 10) % 10;
	d->converted[1] = '0' + (date /= 10) % 10;
	d->converted[0] = '0' + (date /= 10) % 10;
	s_conv(d->converted, d);
}
