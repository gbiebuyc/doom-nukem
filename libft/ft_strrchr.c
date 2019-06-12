/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 10:42:20 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/18 23:25:21 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *res;

	res = 0;
	while (*s)
		if (*s++ == c)
			res = ((char*)(s - 1));
	if (c == '\0')
		return ((char*)s);
	return (res);
}
