/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   widechar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 17:47:50 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/18 23:14:49 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_wcharlen(wchar_t c)
{
	if (c <= 0x7F)
		return (1);
	else if (c <= 0x7FF)
		return (2);
	else if (c <= 0xFFFF)
		return (3);
	return (4);
}

void	ft_putwchar_fd(wchar_t c, int fd)
{
	if (c <= 0x7F)
		ft_putchar_fd(c, fd);
	else if (c <= 0x7FF)
	{
		ft_putchar_fd((c >> 6) | 0xC0, fd);
		ft_putchar_fd((c & 0x3F) | 0x80, fd);
	}
	else if (c <= 0xFFFF)
	{
		ft_putchar_fd((c >> 12) | 0xE0, fd);
		ft_putchar_fd(((c >> 6) & 0x3F) | 0x80, fd);
		ft_putchar_fd((c & 0x3F) | 0x80, fd);
	}
	else if (c <= 0x10FFFF)
	{
		ft_putchar_fd((c >> 18) | 0xF0, fd);
		ft_putchar_fd(((c >> 12) & 0x3F) | 0x80, fd);
		ft_putchar_fd(((c >> 6) & 0x3F) | 0x80, fd);
		ft_putchar_fd((c & 0x3F) | 0x80, fd);
	}
}
