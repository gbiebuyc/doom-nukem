/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fly_gravity.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/29 13:54:16 by nallani           #+#    #+#             */
/*   Updated: 2019/07/09 18:29:30 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define FLYING_SPEED 0.01

static void	fly_gravity_3(t_data *d)
{
	if (!(d->cam.pos.y > d->floorheightplayer + d->player.minimum_height))
		d->player.gravity = 0.0;
	if (!d->player.is_flying)
		d->player.gravity = 0.0;
	d->cam.pos.y += d->player.gravity;
	if (!d->sectors[d->cursectnum].outdoor && d->cam.pos.y > d->ceilheightplayer
			- MINIMUM_CEIL_DIST)
	{
		d->player.gravity = 0.0;
		d->cam.pos.y = d->ceilheightplayer - MINIMUM_CEIL_DIST;
	}
}

static void	fly_gravity_2(t_data *d)
{
	if (d->keys[SDL_SCANCODE_SPACE])
	{
		if (d->cam.pos.y <= d->floorheightplayer + JUMP_FIX +
				d->player.minimum_height)
			d->player.gravity = JUMP_FORCE / 2;
		else
			d->player.gravity += FLYING_SPEED * (d->player.gravity < 0 ? 0.6
					: 0.3);
		d->cam.pos.y += FLYING_SPEED;
		decrease_fuel(d);
	}
	else if (d->keys[SDL_SCANCODE_LCTRL])
	{
		d->player.gravity -= (FLYING_SPEED * 0.5);
		d->cam.pos.y -= FLYING_SPEED;
	}
	fly_gravity_3(d);
}

void		fly_gravity(t_data *d)
{
	if (d->cam.pos.y < d->floorheightplayer + d->player.minimum_height)
	{
		if (d->player.gravity < -0.20)
			player_fell(d);
		d->player.gravity = 0.0;
		d->cam.pos.y = d->floorheightplayer + d->player.minimum_height;
	}
	if (!d->keys[SDL_SCANCODE_SPACE] && d->cam.pos.y <= d->floorheightplayer +
			JUMP_FIX + d->player.minimum_height)
	{
		normal_gravity(d);
		return ;
	}
	if (d->cam.pos.y > d->floorheightplayer + d->player.minimum_height &&
			!d->keys[SDL_SCANCODE_SPACE])
		d->player.gravity -= 0.002;
	fly_gravity_2(d);
}
