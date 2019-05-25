/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 18:27:55 by mikorale          #+#    #+#             */
/*   Updated: 2018/10/23 18:23:17 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		my_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && i < INT_MAX)
		i++;
	return (i);
}

int			write_n(const char c, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		ft_fputc(c, stdout);
		i++;
	}
	return (i);
}

/*
** Set prefix if Hash '#' is use, AND ONLY on non-zero numbers
** 0 for Octal -> 'o'
** 0x/0X for hexadecimal -> 'x' 'X'
*/

static void	set_prefix(t_f_id *id, int *len_prefix, char **prefix)
{
	char c;

	c = id->conv_type;
	if ((!id->flag->hash || (id->arg_int == 0 && id->arg_uint == 0))
		&& !(id->flag->hash && id->conv_type == 'o')
		&& !(id->conv_type == 'p'))
		return ;
	if (c == 'x' || c == 'X' || c == 'p')
	{
		*len_prefix = 2;
		*prefix = (c == 'X') ? "0X" : "0x";
	}
	if (c == 'o')
	{
		*len_prefix = 1;
		*prefix = "0";
	}
}

/*
**	l-P = prefix length
*/

int			print(size_t len, t_f_id *id)
{
	int		count;
	int		l_p;
	char	*prefix;
	char	zero_space;
	char	c;

	count = 0;
	l_p = 0;
	c = id->conv_type;
	zero_space = (c != 'd' && id->flag->zero && (id->preci < 0)) ? '0' : ' ';
	set_prefix(id, &l_p, &prefix);
	if (c == 'o' && id->conv_res && id->conv_res[0] == '0')
		l_p = 0;
	id->field -= l_p;
	count += (l_p && zero_space == '0') ? my_fputs(prefix, stdout, l_p) : 0;
	if (!id->flag->hyphen && id->field > len)
		count += write_n(zero_space, id->field - len);
	count += (l_p && zero_space == ' ') ? my_fputs(prefix, stdout, l_p) : 0;
	count += my_fputs(id->conv_res, stdout, len);
	if (id->flag->hyphen && id->field > len)
		count += write_n(' ', (id->field - len));
	if (id->conv_res && id->conv_type != 's')
		free(id->conv_res);
	fflush(stdout);
	return ((id->nbchar == -1) ? -1 : count);
}
