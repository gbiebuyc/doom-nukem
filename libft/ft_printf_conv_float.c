/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_float.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 17:06:18 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/18 23:14:48 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	float_print(t_data *d)
{
	int	padding_len;

	padding_len = ft_max(0, d->field_width - (int)ft_strlen(d->converted) -
			d->precision - (int)ft_strlen(d->prefix));
	(*d->print_count) += padding_len + d->precision +
		ft_strlen(d->converted) + ft_strlen(d->prefix);
	while (!d->zero_padding && !d->left_ajusted && padding_len-- > 0)
		ft_putchar_fd(' ', d->fd);
	ft_putstr_fd(d->prefix, d->fd);
	while (d->zero_padding && !d->left_ajusted && padding_len-- > 0)
		ft_putchar_fd('0', d->fd);
	ft_putstr_fd(d->converted, d->fd);
	while (d->precision--)
	{
		ft_putchar_fd(d->big[0] + '0', d->fd);
		bignum_mul(d->big, 10);
	}
	while (d->left_ajusted && padding_len-- > 0)
		ft_putchar_fd(' ', d->fd);
}

/*
** Warning messy code below
*/

void	split_whole_and_fract_parts(t_data *d)
{
	int		i;
	char	*whole_part;

	i = 0;
	while (d->big[0] == 0 && (i < BIGNUMDIGITS - d->precision))
	{
		bignum_mul(d->big, 10);
		i++;
	}
	whole_part = d->converted;
	while (i < BIGNUMDIGITS - d->precision)
	{
		*whole_part++ = d->big[0] + '0';
		bignum_mul(d->big, 10);
		i++;
	}
	if (whole_part == d->converted)
		*whole_part++ = '0';
	if (d->precision > 0)
		*whole_part++ = '.';
	*whole_part = '\0';
	float_print(d);
}

void	rounding(int fract_len, t_data *d)
{
	t_bignum	tmp;

	if (d->precision <= fract_len - 1)
	{
		bignum_rshift(d->big, fract_len - d->precision - 1);
		bignum_from_int(tmp, 10);
		if (d->big[BIGNUMDIGITS - 1] >= 5)
			bignum_add(d->big, tmp);
		bignum_rshift(d->big, 1);
	}
	split_whole_and_fract_parts(d);
}

void	mantissa_to_bignum(uint64_t mantissa, int64_t exp, t_data *d)
{
	int			i;
	int			fract_len;
	t_bignum	decimal_pow;

	bignum_from_int(d->big, 0);
	i = 64;
	while (exp >= 0 && --i)
	{
		bignum_pow(decimal_pow, 2, exp);
		if (mantissa & ((uint64_t)1 << i))
			bignum_add(d->big, decimal_pow);
		exp--;
	}
	bignum_from_int(decimal_pow, 1);
	fract_len = 0;
	while (i >= 0)
	{
		bignum_mul(d->big, 10);
		bignum_mul(decimal_pow, 5);
		if ((++exp >= 0) && (mantissa & ((uint64_t)1 << --i)))
			bignum_add(d->big, decimal_pow);
		fract_len++;
	}
	rounding(fract_len, d);
}

void	float128_conv(long double f, bool uppercase, t_data *d)
{
	uint64_t	*iee754;
	bool		is_neg;
	uint64_t	exp;
	uint64_t	mantissa;

	iee754 = (uint64_t*)&f;
	mantissa = iee754[0];
	exp = iee754[1] & 0x7FFF;
	is_neg = (iee754[1] >> 15) & 1;
	if (exp == 0x7FFF && mantissa == 0x8000000000000000 && !is_neg)
		return (s_conv(uppercase ? "INF" : "inf", d));
	if (exp == 0x7FFF && mantissa == 0x8000000000000000 && is_neg)
		return (s_conv(uppercase ? "-INF" : "-inf", d));
	if (exp == 0x7FFF && mantissa != 0)
		return (s_conv(uppercase ? "NAN" : "nan", d));
	if (d->precision == -1)
		d->precision = 6;
	get_sign(is_neg, d);
	mantissa_to_bignum(mantissa, exp - 16383, d);
}
