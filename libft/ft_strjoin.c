/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 11:30:01 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/01/18 23:25:20 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char *s3;

	if (!s1 || !s2)
		return (NULL);
	if ((s3 = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
	{
		s3[0] = '\0';
		ft_strcat(s3, s1);
		ft_strcat(s3, s2);
	}
	return (s3);
}
