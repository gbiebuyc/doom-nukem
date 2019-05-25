/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 18:28:30 by mikorale          #+#    #+#             */
/*   Updated: 2018/10/23 14:53:08 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	get_ulen(uintmax_t nb, unsigned int base)
{
	size_t	i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb)
	{
		i++;
		nb /= base;
	}
	return (i);
}

/*
** precision = condition
** this will check if it need more space to handle a prefix
** ex : %#x, 42 => 0x42
** this mean a size of : (2) to handle "42" + (2) to handle the prefix "0x"
** and malloc size of 2 + 2 + 1 for the '\0'
*/

char			*my_uitoa_base(uintmax_t nb, t_f_id *id, int size)
{
	size_t	len;
	char	*s;
	char	*pattern1;
	char	*pattern2;
	int		precision;

	pattern1 = "0123456789abcdef";
	pattern2 = "0123456789ABCDEF";
	precision = (id->flag->zero && !id->flag->hyphen) ? (id->preci - size) : 0;
	precision = (precision < id->preci) ? id->preci : precision;
	len = get_ulen(nb, id->base);
	if (len < (size_t)precision && precision != -1)
		len = (size_t)precision;
	if (!(s = ft_memalloc(len + 1)))
		return (NULL);
	while (len > 0)
	{
		if (id->conv_type == 'x' || id->conv_type == 'p')
			s[len - 1] = pattern1[nb % id->base];
		else
			s[len - 1] = pattern2[nb % id->base];
		len--;
		nb /= id->base;
	}
	return (s);
}

static int		get_len(intmax_t n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static char		*fill(int len, char sign, int isneg, uintmax_t nb)
{
	static char		*pattern;
	char			*s;

	pattern = "0123456789";
	if (!(s = ft_memalloc((size_t)(len + isneg + 1))))
		return (NULL);
	if (sign)
		s[0] = sign;
	while (len > 0)
	{
		s[len + isneg - 1] = pattern[nb % 10];
		len--;
		nb /= 10;
	}
	return (s);
}

char			*my_itoa(t_f_id *id, char sign)
{
	int			isneg;
	uintmax_t	nb;
	int			len;

	isneg = (id->arg_int < 0 || sign) ? 1 : 0;
	len = get_len(id->arg_int);
	len = (len < id->preci) ? id->preci : len;
	if (!id->period && !id->flag->hyphen && id->flag->zero
		&& len < ((int)id->field - isneg))
	{
		len = (int)id->field - isneg;
		if (id->preci > 0)
			len = (int)id->preci;
	}
	nb = (id->arg_int < 0) ? -id->arg_int : id->arg_int;
	if (id->arg_int < 0)
		sign = '-';
	return (fill(len, sign, isneg, nb));
}
