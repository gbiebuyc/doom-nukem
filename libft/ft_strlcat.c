/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 09:26:01 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/18 23:25:20 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char *start_pos;

	start_pos = dst;
	while (*dst && size > 0)
	{
		dst++;
		size--;
	}
	if (*dst == '\0')
	{
		while (*src && size-- > 1)
			*dst++ = *src++;
		*dst = '\0';
	}
	while (*src++)
		dst++;
	return (dst - start_pos);
}
