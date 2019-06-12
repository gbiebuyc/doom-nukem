/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 16:41:18 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/18 23:25:17 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char *s1c;
	unsigned char *s2c;

	s1c = (unsigned char*)s1;
	s2c = (unsigned char*)s2;
	while (n--)
		if (*s1c++ != *s2c++)
			return (*(s1c - 1) - *(s2c - 1));
	return (0);
}
