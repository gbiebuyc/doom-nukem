/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 17:33:04 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/18 23:14:49 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	get_signed(t_data *d, va_list valist)
{
	if (d->len_mod == 0)
		return (va_arg(valist, int));
	else if (d->len_mod == 1)
		return ((char)va_arg(valist, int));
	else if (d->len_mod == 2)
		return ((short int)va_arg(valist, int));
	else if (d->len_mod == 3)
		return (va_arg(valist, long int));
	else if (d->len_mod == 4)
		return (va_arg(valist, long long int));
	else if (d->len_mod == 5)
		return (va_arg(valist, intmax_t));
	else if (d->len_mod == 6)
		return (va_arg(valist, size_t));
	return (0);
}

uintmax_t	get_unsigned(t_data *d, va_list valist)
{
	if (d->len_mod == 0)
		return (va_arg(valist, unsigned int));
	else if (d->len_mod == 1)
		return ((unsigned char)va_arg(valist, unsigned int));
	else if (d->len_mod == 2)
		return ((unsigned short int)va_arg(valist, unsigned int));
	else if (d->len_mod == 3)
		return (va_arg(valist, unsigned long int));
	else if (d->len_mod == 4)
		return (va_arg(valist, unsigned long long int));
	else if (d->len_mod == 5)
		return (va_arg(valist, uintmax_t));
	else if (d->len_mod == 6)
		return (va_arg(valist, size_t));
	return (0);
}

long double	get_float(t_data *d, va_list valist)
{
	if (d->len_mod == 0 || d->len_mod == 3)
		return (va_arg(valist, double));
	else if (d->len_mod == 7)
		return (va_arg(valist, long double));
	return (0);
}
