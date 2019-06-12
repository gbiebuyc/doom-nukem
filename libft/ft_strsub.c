/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 11:12:10 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/18 23:25:22 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*s2;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if ((s2 = (char*)malloc(len + 1)))
	{
		while (len--)
			s2[i++] = s[start++];
		s2[i] = '\0';
	}
	return (s2);
}
