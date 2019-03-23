/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 19:26:34 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/18 23:25:15 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int				sign;
	unsigned long	res;

	sign = 1;
	while (*str == '\t' || *str == '\v' || *str == '\n' ||
			*str == '\r' || *str == '\f' || *str == ' ')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	res = 0;
	while (*str && *str >= '0' && *str <= '9')
	{
		res = res * 10 + *str++ - '0';
		if (sign == 1 && res > 9223372036854775807U)
			return (-1);
		if (sign == -1 && res > 9223372036854775808U)
			return (0);
	}
	return ((int)res * sign);
}
