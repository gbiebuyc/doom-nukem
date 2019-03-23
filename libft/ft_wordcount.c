/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 15:46:25 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/18 23:25:22 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_wordcount(const char *s, char c)
{
	size_t wc;

	wc = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			wc++;
			while (*s && *s != c)
				s++;
		}
	}
	return (wc);
}
