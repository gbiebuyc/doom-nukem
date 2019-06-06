/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inertia.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 00:01:28 by nallani           #+#    #+#             */
/*   Updated: 2019/06/07 00:10:02 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

# define MAX_INERTIA 0.19

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
	d->inertia = mul_vec2f(d->inertia, 0.9);
}
