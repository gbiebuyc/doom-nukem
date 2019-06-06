/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 21:22:40 by nallani           #+#    #+#             */
/*   Updated: 2019/05/15 18:45:24 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define MINIMUM_HEIGHT 0.5
#define JUMP_FORCE 0.08

void	gravity(t_data *d, int mod)
{
	static double	accel;

	if (mod == 1 && (accel = JUMP_FORCE))
		return ;
	if (mod == 2)
	{
		accel += 0.0015;
		return ;
	}
	d->cam.pos.y += accel;
	accel -= 0.004;
	if (d->cam.pos.y > d->sectors[d->cursectnum].ceilheight && accel > 0)
		accel = 0;
	if (d->cam.pos.y < d->sectors[d->cursectnum].floorheight + MINIMUM_HEIGHT)
	{
		accel = 0;
		// if (accel < INSERT_NUMBER == degat_chute(time, d->player))
		d->cam.pos.y = d->sectors[d->cursectnum].floorheight + MINIMUM_HEIGHT;
	}
}

void	jump(t_data *d, bool pressed)
{
	static bool is_jumping;

	if (!pressed)
	{
		is_jumping = false;
		return;
	}
	if (d->cam.pos.y <= d->sectors[d->cursectnum].floorheight + MINIMUM_HEIGHT)
	{
		gravity(d, 1);
		is_jumping = 1;
	}
	else if (is_jumping)
		gravity(d, 2);
}
