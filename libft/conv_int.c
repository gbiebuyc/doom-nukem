/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 18:05:37 by mikorale          #+#    #+#             */
/*   Updated: 2018/10/23 17:51:52 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	0 = l, 1 = ll, 2 = j, 3 = z, 4 = hh, 5 = h
**	check what modifier has been used and convert the argument
**	to the conresponding modifier then set it in id->arg_uint
*/

static void	handle_u_modifier(const char *format, t_f_id *id, va_list ap)
{
	get_modifier(format, id);
	if (id->modifier[0])
		id->arg_uint = va_arg(ap, unsigned long);
	else if (id->modifier[1])
		id->arg_uint = va_arg(ap, unsigned long long);
	else if (id->modifier[2])
		id->arg_uint = va_arg(ap, uintmax_t);
	else if (id->modifier[3])
		id->arg_uint = va_arg(ap, size_t);
	else
	{
		id->arg_uint = va_arg(ap, unsigned int);
		if (id->modifier[4])
			id->arg_uint = (unsigned char)id->arg_uint;
		else if (id->modifier[5])
			id->arg_uint = (unsigned short)id->arg_uint;
	}
}

static void	handle_modifier(const char *format, t_f_id *id, va_list ap)
{
	get_modifier(format, id);
	if (id->modifier[0])
		id->arg_int = va_arg(ap, long);
	else if (id->modifier[1])
		id->arg_int = va_arg(ap, long long);
	else if (id->modifier[2])
		id->arg_int = va_arg(ap, intmax_t);
	else if (id->modifier[3])
		id->arg_int = va_arg(ap, ssize_t);
	else
	{
		id->arg_int = va_arg(ap, int);
		if (id->modifier[4])
			id->arg_int = (char)id->arg_int;
		else if (id->modifier[5])
			id->arg_int = (short)id->arg_int;
	}
}

/*
** Call handle modifier that will get the argument value and convert it
** to the correct type depending on which modifier has been used.
** Pre-set the variable sign, in the order they overwrite each other,
** so we can handle that flag later by sending the "sign" into "my_iota"
*/

static int	conv_d(const char *format, va_list ap, t_f_id *id)
{
	int		count;
	char	sign;

	sign = '\0';
	count = 0;
	handle_modifier(format, id, ap);
	if (id->flag->plus)
		sign = '+';
	else if (id->flag->blank)
		sign = ' ';
	if (id->preci == 0 && id->arg_int == 0)
		id->conv_res = (sign == '\0') ? NULL : ft_strdup(&sign);
	else
		id->conv_res = my_itoa(id, sign);
	count += print(my_strlen(id->conv_res), id);
	return (count);
}

/*
** if the conv_type is 'd' or 'i', it will just handle signed int,
** by calling "conv_d".
** if the conv_type is different than 'd/i', it will handle all others
** types calling "handle_u_modifier" which handle all unsigned types.
** if the flag "#" is used we will save 1 or 2 more slots to handle prefix.
** 'x/X/p' = 0x -> 2 slots, 'o' = 0 -> 1 slot
*/

int			conv_int(const char *format, va_list ap, t_f_id *id)
{
	int		count;
	char	c;
	int		size;

	get_flags(format, id);
	get_field_n_preci(format + id->i, id);
	c = id->conv_type;
	if (c == 'd')
		return (conv_d(format, ap, id));
	id->base = (unsigned int)get_base(c);
	count = 0;
	size = 0;
	if (id->flag->hash || c == 'p')
		size = (c == 'o') ? 1 : 2;
	handle_u_modifier(format, id, ap);
	if ((id->preci == 0 && id->arg_uint == 0 && id->flag->hash) ||
		(id->preci == 0 && id->arg_uint == 0))
		id->conv_res = NULL;
	else
		id->conv_res = my_uitoa_base(id->arg_uint, id, size);
	count += print(my_strlen(id->conv_res), id);
	return (count);
}
