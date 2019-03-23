/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 11:40:57 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/18 23:25:22 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

char		*ft_strtrim(char const *s)
{
	unsigned int	i;
	unsigned int	start;
	unsigned int	end;

	if (!s)
		return (NULL);
	i = 0;
	while (is_space(s[i]))
		i++;
	start = i;
	end = i;
	while (s[i])
	{
		while (!is_space(s[i]) && s[i])
			i++;
		end = i;
		while (is_space(s[i]))
			i++;
	}
	return (ft_strsub(s, start, end - start));
}
