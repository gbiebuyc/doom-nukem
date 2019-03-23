/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 13:24:59 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/18 23:25:15 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(const char *s)
{
	double	res;
	int		sign;
	int		div;

	sign = 1;
	while (*s == '\t' || *s == '\v' || *s == '\n' ||
			*s == '\r' || *s == '\f' || *s == ' ')
		s++;
	if (*s == '-')
		sign = -1;
	if (*s == '-' || *s == '+')
		s++;
	res = 0;
	while (*s >= '0' && *s <= '9')
		res = res * 10 + *s++ - '0';
	if (*s++ == '.')
	{
		div = 1;
		while (*s >= '0' && *s <= '9')
		{
			div *= 10;
			res += (double)(*s++ - '0') / div;
		}
	}
	return (res * sign);
}
