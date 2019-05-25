/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wide_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 10:39:29 by mikorale          #+#    #+#             */
/*   Updated: 2018/10/23 17:30:27 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	my_wcharlen(wchar_t wc)
{
	if ((wc >= 0xD800 && wc <= 0xDFFF) || wc > 0x10FFFF || wc < 0)
		return (0);
	if (wc <= 0x007F)
		return (1);
	else if (wc <= 0x07FF)
		return (2);
	else if (wc <= 0xFFFF)
		return (3);
	else if (wc <= 0x10FFFF)
		return (4);
	return (0);
}

size_t	my_wstrlen(wchar_t *ws)
{
	size_t	i;
	size_t	valid;

	i = 0;
	while (*ws != L'\0')
	{
		if ((valid = my_wcharlen(*ws)) == 0)
			return (0);
		i += valid;
		ws++;
	}
	return (i);
}

/*
**	Get the wide precision.
**	In UTF-8 Characters can be longer than one 'char' wide (1 byte),
**	so it's possible to have a specified precision higher than the
**	number of printable utf-9 chars.
**
**	Example: ft_printf("%10.5S", L"我是");
**	The precision is 5 but the utf-8 char '我' is 3 'chars' wide
**	and the '是' char can't be printed with only 2 'char' of precision left.
**
**	https://www.fileformat.info/info/charset/UTF-8/list.htm
**	https://en.wikipedia.org/wiki/UTF-8
**
**	Increase the new precision until it reach the end of the wstr, or until
**	the specified precision is equal to zero, or if a widechar is larger
**	than 0x10FFFF (the last UTF-8 char)
*/

size_t	get_wpreci(wchar_t *wstr, int idpreci, size_t preci)
{
	if (*wstr == L'\0' || idpreci == 0)
		return (preci);
	else if (*wstr <= 0x007F)
		return (get_wpreci(wstr + 1, idpreci - 1, preci + 1));
	else if (*wstr <= 0x07FF && idpreci >= 2)
		return (get_wpreci(wstr + 1, idpreci - 2, preci + 2));
	else if (*wstr <= 0xFFFF && idpreci >= 3)
		return (get_wpreci(wstr + 1, idpreci - 3, preci + 3));
	else if (*wstr <= 0x10FFFF && idpreci >= 4)
		return (get_wpreci(wstr + 1, idpreci - 4, preci + 4));
	else
		return (preci);
}

/*
** https://en.wikipedia.org/wiki/UTF-8
** https://en.wikipedia.org/wiki/Bitwise_operations_in_C
*/

int		my_putwchar(wint_t wc)
{
	int	count;

	count = 0;
	if (wc <= 0x007F)
		count += write_n(wc, 1);
	else if (wc <= 0x07FF)
	{
		count += write_n(((wc >> 6) | 0xC0), 1);
		count += write_n(((wc & 0x3F) | 0x80), 1);
	}
	else if (wc <= 0xFFFF)
	{
		count += write_n(((wc >> 12) | 0xE0), 1);
		count += write_n((((wc >> 6) & 0x3F) | 0x80), 1);
		count += write_n(((wc & 0x3F) | 0x80), 1);
	}
	else if (wc <= 0x10FFFF)
	{
		count += write_n(((wc >> 18) | 0xF0), 1);
		count += write_n((((wc >> 12) & 0x3F) | 0x80), 1);
		count += write_n((((wc >> 6) & 0x3F) | 0x80), 1);
		count += write_n(((wc & 0x3F) | 0x80), 1);
	}
	return (count);
}

int		my_putwstr(wchar_t *wstr, size_t len)
{
	size_t	i;

	i = 0;
	while (*wstr && i < len)
	{
		if (*wstr <= 0x7F)
			i++;
		else if (*wstr <= 0x07FF)
			i += 2;
		else if (*wstr <= 0xFFFF)
			i += 3;
		else if (*wstr <= 0x10FFFF)
			i += 4;
		if (i <= len)
			my_putwchar(*wstr++);
	}
	return ((int)len);
}
