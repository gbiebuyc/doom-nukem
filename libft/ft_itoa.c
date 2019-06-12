/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 17:27:38 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/18 23:25:16 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_str(char *str, int n, int div)
{
	if (n < 0)
	{
		*str++ = '-';
		n = -n;
	}
	while (div)
	{
		*str++ = '0' + (n / div) % 10;
		div /= 10;
	}
	*str = '\0';
}

char		*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		div;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	len = 10;
	div = 1000000000;
	while (len > 0 && n / div == 0)
	{
		div /= 10;
		len--;
	}
	if (!(str = (char*)malloc(len + ((n < 0) ? 2 : 1))))
		return (0);
	fill_str(str, n, div);
	return (str);
}
