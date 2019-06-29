/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 16:31:22 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/29 14:00:03 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

double	lerp(double norm, double min, double max)
{
	return (min * (1 - norm) + max * norm);
}

double	norm(double val, double min, double max)
{
	return ((val - min) / (max - min));
}

int		clamp(int x, int min, int max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

double	fclamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

int		ft_mod(int i, int n)
{
	return ((i % n + n) % n);
}
