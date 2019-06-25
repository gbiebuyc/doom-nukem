/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inertia.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 00:01:28 by nallani           #+#    #+#             */
/*   Updated: 2019/06/25 23:39:08 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define MAX_INERTIA 0.19

void	inertia(t_data *d, t_vec2f mvt)
{
	double	angle;

	d->inertia.x += mvt.x;
	d->inertia.y += mvt.y;
	if (vec2f_length(d->inertia) > MAX_INERTIA)
	{
		angle = atan2(d->inertia.y, d->inertia.x) - M_PI_2;
		d->inertia.x = 0.0;
		d->inertia.y = MAX_INERTIA;
		actualize_dir(angle, &d->inertia);
	}
	if (vec2f_length(d->inertia) > 0.001)
		d->inertia = mul_vec2f(d->inertia, 0.9);
	else
	{
		d->inertia.x = 0;
		d->inertia.y = 0;
	}
}

void	change_inertia(t_data *d, double angle, double length)
{
	d->inertia.x = length;
	d->inertia.y = 0.0;
	actualize_dir(angle, &d->inertia);
}
