/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 13:22:51 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/02/01 18:52:45 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool		fill_arr(char **arr, const char *s, char c)
{
	size_t word_len;

	while (*s == c)
		s++;
	if (!*s)
	{
		*arr = NULL;
		return (true);
	}
	word_len = 0;
	while (s[word_len] && s[word_len] != c)
		word_len++;
	if (!(*arr = ft_strsub(s, 0, word_len)))
		return (false);
	if (!fill_arr(arr + 1, s + word_len, c))
	{
		free(*arr);
		return (false);
	}
	return (true);
}

char			**ft_strsplit(char const *s, char c)
{
	char **arr;

	if (!s)
		return (NULL);
	if (!(arr = (char**)malloc(sizeof(char*) * (ft_wordcount(s, c) + 1))))
		return (NULL);
	if (!fill_arr(arr, s, c))
	{
		free(arr);
		return (NULL);
	}
	return (arr);
}
