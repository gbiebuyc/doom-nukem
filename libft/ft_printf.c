/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 18:05:32 by mikorale          #+#    #+#             */
/*   Updated: 2018/10/23 18:24:05 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** 0 = L	long
** 1 = LL	long long
*/

static void	fix_conv_type(t_f_id *id)
{
	char c;

	c = id->conv_type_origin;
	id->conv_type = id->conv_type_origin;
	if (c == 'C' || c == 'D' || c == 'O' || c == 'S' || c == 'U')
		id->modifier[0] = 1;
	if (c == 'p')
		id->modifier[1] = 2;
	if (c == 'C')
		id->conv_type = 'c';
	else if (c == 'O')
		id->conv_type = 'o';
	else if (c == 'D' || c == 'i')
		id->conv_type = 'd';
	else if (c == 'U')
		id->conv_type = 'u';
	else if (c == 'S')
		id->conv_type = 's';
}

/*
** This function check what follow the '%'.
** If flags nor field nor precision is used,
** the function will skip everything until it find the argument type,
** and will return the index of the argument type.
** If no argument is found the function return -99 as an error,
** meaning the string isn't well formated.
*/

static int	get_conv_type(const char *format, t_f_id *id)
{
	int			i;
	const char	*tmp;
	char		*conv_pattern;

	tmp = format;
	conv_pattern = "cCdDioOpsSuUxX%";
	format++;
	while (tododge(*format))
		format++;
	i = 0;
	while (conv_pattern[i])
	{
		if (*format == conv_pattern[i])
		{
			id->conv_type_origin = conv_pattern[i];
			fix_conv_type(id);
			return (i);
		}
		i++;
	}
	id->conv_type_origin = *format;
	id->conv_type = *format;
	id->invalid = 1;
	return (-1);
}

/*
** displqy '%' if '%%' is detect
** if not : get the list of conversion functions
** and start the conversion of the argument by calling g_conv_list
** g_conv_list contains the list of all the functions,
** each one converting a specific type
*/

static int	handle_conv(const char *format, va_list ap, t_f_id *id)
{
	t_flag	flag;
	int		ret;

	id->flag = &flag;
	init(id);
	if ((id->conv_id = get_conv_type(format, id)) == -1)
	{
		if (id->conv_type != '\0')
			id->nbchar += g_conv_list[1](format, ap, id);
		return (-1);
	}
	ret = g_conv_list[id->conv_id](format, ap, id);
	id->nbchar = (ret == -1 || id->nbchar == -1) ? -1 : (id->nbchar + ret);
	return (id->nbchar);
}

/*
** If '%' is find, handle the conversion.
** If not, write each character until a '%' is found,
** or until the end of the string.
** i = the index of the stringi format
*/

static void	handler(const char *format, va_list ap, t_f_id *id, size_t i)
{
	while (*(format + i))
	{
		if (*(format + i) == '%' && *(format + i + 1) == '%')
		{
			id->nbchar = (id->nbchar == -1) ? -1 : id->nbchar + 1;
			ft_fputc('%', stdout);
			i++;
		}
		else if (*(format + i) == '%' && *(format + i + 1))
		{
			handle_conv(format + i, ap, id);
			(id->error == -1) ? FPURGE(stdout) : 1;
			if (id->error == -1)
				return ;
			i++;
			while (*(format + i) != id->conv_type_origin && *(format + i + 1))
				i++;
		}
		else if (*(format + i) != '%')
		{
			ft_fputc(*(format + i), stdout);
			id->nbchar = (id->nbchar == -1) ? -1 : id->nbchar + 1;
		}
		i++;
	}
}

int			ft_printf(const char *format, ...)
{
	va_list			ap;
	static t_f_id	id;

	id.nbchar = (id.nbchar == -1) ? -1 : 0;
	id.error = 0;
	va_start(ap, format);
	get_conv_list();
	handler(format, ap, &id, 0);
	va_end(ap);
	return (id.nbchar);
}
