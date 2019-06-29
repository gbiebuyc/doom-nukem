/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 21:22:40 by nallani           #+#    #+#             */
/*   Updated: 2019/06/29 13:59:49 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define CROUCH_SPEED 0.01

void	check_crouch(t_data *d)
{
	if (d->cam.pos.y <= d->floorheightplayer + d->player.minimum_height)
	{
		if (d->keys[SDL_SCANCODE_LCTRL] && d->player.minimum_height >
				MINIMUM_CROUCH_HEIGHT + CROUCH_SPEED)
			d->player.minimum_height -= CROUCH_SPEED;
		if (!d->keys[SDL_SCANCODE_LCTRL] && d->player.minimum_height
				< MINIMUM_HEIGHT)
			if ((d->ceilheightplayer - d->floorheightplayer - MINIMUM_CEIL_DIST)
					> d->player.minimum_height + CROUCH_SPEED)
				d->player.minimum_height += CROUCH_SPEED;
	}
	if (d->keys[SDL_SCANCODE_SPACE])
	{
		if (d->ceilheightplayer - d->floorheightplayer - MINIMUM_CEIL_DIST <=
				MINIMUM_HEIGHT)
			d->player.minimum_height = d->ceilheightplayer -
				d->floorheightplayer - MINIMUM_CEIL_DIST - CROUCH_SPEED;
		else
			d->player.minimum_height = MINIMUM_HEIGHT;
	}
	if (d->player.minimum_height < MINIMUM_CROUCH_HEIGHT)
		d->player.minimum_height += CROUCH_SPEED + CROUCH_SPEED + CROUCH_SPEED;
}

void	normal_gravity(t_data *d)
{
	if (d->cam.pos.y < d->floorheightplayer + d->player.minimum_height)
	{
		if (d->player.gravity < -0.16)
			player_fell(d);
		d->player.gravity = 0.0;
		d->cam.pos.y = d->floorheightplayer + d->player.minimum_height;
	}
	if (d->cam.pos.y <= d->floorheightplayer + JUMP_FIX +
			d->player.minimum_height && d->keys[SDL_SCANCODE_SPACE])
		d->player.gravity = JUMP_FORCE;
	if (d->cam.pos.y > d->floorheightplayer + d->player.minimum_height)
	{
		d->player.gravity -= 0.004;
		if (d->player.gravity > 0 && d->keys[SDL_SCANCODE_SPACE])
			d->player.gravity += 0.0015;
	}
	check_crouch(d);
	d->cam.pos.y += d->player.gravity;
	if (!d->sectors[d->cursectnum].outdoor && d->cam.pos.y > d->ceilheightplayer
			- MINIMUM_CEIL_DIST)
	{
		d->player.gravity = 0.0;
		d->cam.pos.y = d->ceilheightplayer - MINIMUM_CEIL_DIST;
	}
}

void	jump(t_data *d)
{
	if (d->player.is_flying)
		fly_gravity(d);
	else
		normal_gravity(d);
}
