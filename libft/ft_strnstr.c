/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 09:45:59 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/18 23:25:21 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;

	if (*needle == '\0')
		return ((char*)haystack);
	while (*haystack && len > 0)
	{
		i = 0;
		while (haystack[i] && haystack[i] == needle[i])
			i++;
		if (i > len)
			return (NULL);
		if (needle[i] == '\0')
			return ((char*)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
