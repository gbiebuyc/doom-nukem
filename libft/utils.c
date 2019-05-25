/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 19:09:26 by mikorale          #+#    #+#             */
/*   Updated: 2018/08/13 15:56:31 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** While the char in the *format isn't a number > 0 or isn't a dot AND
** isn't the argument type, e handle (save&skip) all flags found
** this can handle something like -> ft_printf("%-  --   ---- 10.5d")
** or ft_printf("%++++000+++000+0+0+0++010.5d")
*/

void	get_flags(const char *format, t_f_id *id)
{
	int	i;
	int	test;

	i = 0;
	test = 0;
	while (*(format + i) != id->conv_type_origin)
	{
		if (((*(format + i) >= '1' && *(format + i) <= '9') ||
				*(format + i) == '.') && id->i == 0 && test != 1)
		{
			id->i = i;
			test = 1;
		}
		if (*(format + i) == '-')
			id->flag->hyphen = 1;
		if (*(format + i) == '+')
			id->flag->plus = 1;
		if (*(format + i) == '#')
			id->flag->hash = 1;
		if (*(format + i) == '0' && id->i == 0)
			id->flag->zero = 1;
		if (*(format + i) == ' ')
			id->flag->blank = 1;
		i++;
	}
}

void	get_modifier(const char *format, t_f_id *id)
{
	while (*format != id->conv_type_origin)
	{
		if (*format == 'l' && *(format + 1) != 'l' && *(format - 1) != 'l')
			id->modifier[0] = 1;
		if (*format == 'l' && *(format + 1) == 'l')
			id->modifier[1] = 1;
		if (*format == 'j')
			id->modifier[2] = 1;
		if (*format == 'z')
			id->modifier[3] = 1;
		if (*format == 'h' && *(format + 1) == 'h')
			id->modifier[4] = 1;
		if (*format == 'h' && *(format + 1) != 'h' && *(format - 1) != 'h')
			id->modifier[5] = 1;
		format++;
	}
}

/*
** Start with index 'i' = 0, this will count how many numbers have been
** specified in the string format, it will skip all digit until it find
** a dot or the argument type (cCdDisS ...)
** Copy the numbers in to id->field_min (we found the minimum field size).
** If it previously found a dot, notice that a period exist (id->period = 1)
** and it will now use the same process to get the precision.
*/

void	get_field_n_preci(const char *format, t_f_id *id)
{
	char	*str;
	int		i;

	i = 0;
	while (*(format + i) != id->conv_type_origin && *(format + i) != '.')
		i++;
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return ;
	str[i] = '\0';
	id->field = (i != 0) ? (size_t)ft_atoi(ft_strncpy(str, format, i)) : 0;
	if (*(format + i) == '.')
	{
		id->preci = 0;
		id->period = 1;
		if (*(format + i + 1) >= '0' && *(format + i + 1) <= '9')
		{
			format += i;
			i = 0;
			while (*(format + i) != id->conv_type_origin)
				i++;
			id->preci = ft_atoi(ft_strncpy(str, format + 1, i));
		}
	}
	if (str != NULL)
		free(str);
}

int		get_base(char c)
{
	if (c == 'o')
		return (8);
	else if (c == 'x' || c == 'X' || c == 'p')
		return (16);
	else
		return (10);
}

int		tododge(char c)
{
	char	*dodge;

	dodge = "-+ 0#hljz123456789.*$L'";
	while (*dodge)
	{
		if (c == *dodge)
			return (1);
		dodge++;
	}
	return (0);
}
