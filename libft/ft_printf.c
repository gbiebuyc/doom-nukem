/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 15:29:35 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/27 00:08:51 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse(char *s, va_list valist, int *print_count, int fd)
{
	t_data	d;

	*print_count = 0;
	while (*s)
	{
		if (*s == '{')
			parse_color(&s, print_count, fd);
		else if (*s == '%')
		{
			s++;
			d = (t_data){.print_count = print_count, .fd = fd};
			parse_flags(&s, &d);
			parse_field_width(&s, &d, valist);
			parse_precision(&s, &d, valist);
			parse_len_modifier(&s, &d);
			convert(&s, &d, valist);
		}
		else
		{
			ft_putchar_fd(*s++, fd);
			(*print_count)++;
		}
	}
}

int		ft_dprintf(int fd, const char *format, ...)
{
	va_list valist;
	int		print_count;

	va_start(valist, format);
	parse((char*)format, valist, &print_count, fd);
	va_end(valist);
	return (print_count);
}

int		ft_printf(const char *format, ...)
{
	va_list valist;
	int		print_count;

	va_start(valist, format);
	parse((char*)format, valist, &print_count, 1);
	va_end(valist);
	return (print_count);
}
