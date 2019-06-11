/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:38:44 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/27 02:59:17 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_color(char **format, int *print_count, int fd)
{
	int	len;
	int	len2;

	len2 = 0;
	if (ft_strnequ(*format, "{red}", (len = 5)))
		ft_putstrn_fd(fd, "\e[31m", (len2 = 5));
	else if (ft_strnequ(*format, "{green}", (len = 7)))
		ft_putstrn_fd(fd, "\e[32m", (len2 = 5));
	else if (ft_strnequ(*format, "{yellow}", (len = 8)))
		ft_putstrn_fd(fd, "\e[33m", (len2 = 5));
	else if (ft_strnequ(*format, "{blue}", (len = 6)))
		ft_putstrn_fd(fd, "\e[34m", (len2 = 5));
	else if (ft_strnequ(*format, "{magenta}", (len = 9)))
		ft_putstrn_fd(fd, "\e[35m", (len2 = 5));
	else if (ft_strnequ(*format, "{cyan}", (len = 6)))
		ft_putstrn_fd(fd, "\e[36m", (len2 = 5));
	else if (ft_strnequ(*format, "{eoc}", (len = 5)))
		ft_putstrn_fd(fd, "\e[0m", (len2 = 4));
	else if (ft_strnequ(*format, "{bold}", (len = 6)))
		ft_putstrn_fd(fd, "\e[1m", (len2 = 4));
	else if (ft_strnequ(*format, "{", (len = 1)))
		ft_putstrn_fd(fd, "{", (len2 = 1));
	(*format) += len;
	(*print_count) += len2;
}

void	parse_flags(char **s, t_data *d)
{
	while (**s)
	{
		if (**s == '#')
			d->alternate_form = true;
		else if (**s == '0')
			d->zero_padding = true;
		else if (**s == '-')
			d->left_ajusted = true;
		else if (**s == ' ')
			d->space_before_positive_num = true;
		else if (**s == '+')
			d->show_plus_sign = true;
		else
			return ;
		(*s)++;
	}
}

void	parse_field_width(char **s, t_data *d, va_list valist)
{
	while (**s)
	{
		if (**s == '*')
		{
			d->field_width = va_arg(valist, int);
			if (d->field_width < 0)
			{
				d->field_width = -d->field_width;
				d->left_ajusted = true;
			}
			(*s)++;
		}
		else if (ft_isdigit(**s))
		{
			d->field_width = 0;
			while (ft_isdigit(**s))
				d->field_width = d->field_width * 10 + *(*s)++ - '0';
		}
		else
			break ;
	}
	parse_flags(s, d);
}

void	parse_precision(char **s, t_data *d, va_list valist)
{
	d->precision = -1;
	while (**s)
	{
		if (**s == '.')
		{
			(*s)++;
			if (**s == '*')
			{
				d->precision = va_arg(valist, int);
				(*s)++;
			}
			else
			{
				d->precision = 0;
				while (ft_isdigit(**s))
					d->precision = d->precision * 10 + *(*s)++ - '0';
			}
		}
		else
			break ;
	}
	parse_flags(s, d);
}

void	parse_len_modifier(char **s, t_data *d)
{
	int	len;

	d->len_mod = 0;
	while (**s)
	{
		if (ft_strnequ(*s, "hh", (len = 2)))
			d->len_mod = ft_max(1, d->len_mod);
		else if (ft_strnequ(*s, "h", (len = 1)))
			d->len_mod = ft_max(2, d->len_mod);
		else if (ft_strnequ(*s, "ll", (len = 2)))
			d->len_mod = ft_max(4, d->len_mod);
		else if (ft_strnequ(*s, "l", (len = 1)))
			d->len_mod = ft_max(3, d->len_mod);
		else if (ft_strnequ(*s, "j", (len = 1)))
			d->len_mod = ft_max(5, d->len_mod);
		else if (ft_strnequ(*s, "z", (len = 1)))
			d->len_mod = ft_max(6, d->len_mod);
		else if (ft_strnequ(*s, "L", (len = 1)))
			d->len_mod = ft_max(7, d->len_mod);
		else
			break ;
		(*s) += len;
	}
	parse_flags(s, d);
}
