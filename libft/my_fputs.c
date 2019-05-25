/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fputs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 13:50:57 by mikorale          #+#    #+#             */
/*   Updated: 2018/10/23 14:53:51 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		my_fputs(char *s, FILE *stream, size_t len)
{
	fwrite(s, len, sizeof(char), stream);
	return ((int)len);
}
