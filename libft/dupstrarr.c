/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dupstrarr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 01:34:25 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/02/04 01:46:07 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	duplicate(char **arr1, char **arr2)
{
	if (!*arr1)
		*arr2 = NULL;
	else
	{
		if (!(*arr2 = ft_strdup(*arr1)))
			return (false);
		if (!duplicate(arr1 + 1, arr2 + 1))
		{
			free(*arr2);
			return (false);
		}
	}
	return (true);
}

char	**dupstrarr(char **arr1)
{
	size_t	len;
	char	**arr2;

	if (!arr1)
		return (NULL);
	len = 0;
	while (arr1[len])
		len++;
	if (!(arr2 = malloc(sizeof(*arr2) * (len + 1))))
		return (NULL);
	if (!(duplicate(arr1, arr2)))
	{
		free(arr2);
		return (NULL);
	}
	return (arr2);
}
