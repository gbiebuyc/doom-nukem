/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 09:43:06 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/18 23:25:20 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*s2;

	if (!s || !f)
		return (0);
	i = 0;
	while (s[i])
		i++;
	if ((s2 = (char*)malloc(i + 1)))
	{
		i = -1;
		while (s[++i])
			s2[i] = (*f)(i, s[i]);
		s2[i] = '\0';
	}
	return (s2);
}
