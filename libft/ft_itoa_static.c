/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_static.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 14:06:33 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/18 23:25:16 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Same as ft_itoa but without malloc.
*/

char	*ft_itoa_static(intmax_t n)
{
	uintmax_t	tmpn;
	uintmax_t	div;
	static char	s[42];
	int			i;

	i = 0;
	if (n < 0)
	{
		s[i++] = '-';
		n = -n;
	}
	tmpn = n;
	div = 1;
	while (tmpn /= 10)
		div *= 10;
	while (div)
	{
		s[i++] = n / div % 10 + '0';
		div /= 10;
	}
	s[i] = '\0';
	return (s);
}
