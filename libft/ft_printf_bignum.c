/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 15:17:38 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/18 23:14:47 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	bignum_from_int(t_bignum big, unsigned int n)
{
	int	i;

	i = BIGNUMDIGITS;
	while (--i >= 0)
	{
		big[i] = n % 10;
		n /= 10;
	}
}

void	bignum_add(t_bignum dst, t_bignum src)
{
	int	carry;
	int	tmp;
	int	i;

	carry = 0;
	i = BIGNUMDIGITS;
	while (--i >= 0)
	{
		tmp = (int)dst[i] + (int)src[i] + carry;
		dst[i] = tmp % 10;
		carry = tmp / 10;
	}
}

void	bignum_mul(t_bignum big, int n)
{
	int	carry;
	int	tmp;
	int	i;

	carry = 0;
	i = BIGNUMDIGITS;
	while (--i >= 0)
	{
		tmp = n * (int)big[i] + carry;
		big[i] = tmp % 10;
		carry = tmp / 10;
	}
}

void	bignum_rshift(t_bignum big, unsigned int shift)
{
	int	i;

	i = BIGNUMDIGITS;
	while (--i >= 0)
	{
		if ((i - (int)shift) >= 0)
			big[i] = big[i - (int)shift];
		else
			big[i] = 0;
	}
}

void	bignum_pow(t_bignum big, unsigned int x, unsigned int y)
{
	bignum_from_int(big, 1);
	while (y--)
		bignum_mul(big, x);
}
