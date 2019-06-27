/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 21:22:40 by nallani           #+#    #+#             */
/*   Updated: 2019/06/18 00:47:45 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

# define MINIMUM_CROUCH_HEIGHT 0.2 // defined in player_damage too
# define CROUCH_SPEED 0.01
# define MINIMUM_CEIL_DIST 0.1 // defined in movement aswell
# define JUMP_FIX 0.01

void	check_crouch(t_data *d)
{
	if (d->cam.pos.y <= d->floorheightplayer + d->player.minimum_height)
	{
		if (d->keys[SDL_SCANCODE_LCTRL] && d->player.minimum_height > MINIMUM_CROUCH_HEIGHT + CROUCH_SPEED)
			d->player.minimum_height -= CROUCH_SPEED;
		if (!d->keys[SDL_SCANCODE_LCTRL] && d->player.minimum_height < MINIMUM_HEIGHT)
			if ((d->ceilheightplayer - d->floorheightplayer - MINIMUM_CEIL_DIST) >
					d->player.minimum_height + CROUCH_SPEED) // used for crouching in small sector
			d->player.minimum_height += CROUCH_SPEED;
	}
	if (d->keys[SDL_SCANCODE_SPACE])
	{
		if (d->ceilheightplayer - d->floorheightplayer - MINIMUM_CEIL_DIST <= MINIMUM_HEIGHT)
			d->player.minimum_height = d->ceilheightplayer - d->floorheightplayer - MINIMUM_CEIL_DIST -
				CROUCH_SPEED;
		else
			d->player.minimum_height = MINIMUM_HEIGHT;
	}
	if (d->player.minimum_height < MINIMUM_CROUCH_HEIGHT)
		d->player.minimum_height += CROUCH_SPEED + CROUCH_SPEED + CROUCH_SPEED;
}

# define JUMP_FORCE 0.08

void	normal_gravity(t_data *d)
{
	if (d->cam.pos.y < d->floorheightplayer + d->player.minimum_height)
	{
		if (d->player.gravity < -0.16)
			player_fell(d);
		d->player.gravity = 0.0;
		d->cam.pos.y = d->floorheightplayer + d->player.minimum_height;
	}
	if (d->cam.pos.y <= d->floorheightplayer + JUMP_FIX + d->player.minimum_height && d->keys[SDL_SCANCODE_SPACE])
		d->player.gravity = JUMP_FORCE;
	if (d->cam.pos.y > d->floorheightplayer + d->player.minimum_height)
	{
		d->player.gravity -= 0.004;
		if (d->player.gravity > 0 && d->keys[SDL_SCANCODE_SPACE])
			d->player.gravity += 0.0015;
	}
	check_crouch(d);
	d->cam.pos.y += d->player.gravity;
	if (!d->sectors[d->cursectnum].outdoor && d->cam.pos.y > d->ceilheightplayer - MINIMUM_CEIL_DIST)
	{
		d->player.gravity = 0.0;
		d->cam.pos.y = d->ceilheightplayer - MINIMUM_CEIL_DIST;
	}
}

#define FLYING_SPEED 0.01

void	fly_gravity(t_data *d)
{
	if (d->cam.pos.y < d->floorheightplayer + d->player.minimum_height)
	{
		// do damage with d->player.gravity
		d->player.gravity = 0.0;
		d->cam.pos.y = d->floorheightplayer + d->player.minimum_height;
	}
	if (!d->keys[SDL_SCANCODE_SPACE] && d->cam.pos.y <= d->floorheightplayer + JUMP_FIX + 
			d->player.minimum_height)
	{
		normal_gravity(d);
		return ;
	}	
	d->player.gravity -= 0.002;
	if (d->keys[SDL_SCANCODE_SPACE])
	{
		d->player.gravity += (FLYING_SPEED * (d->player.gravity < 0 ? 0.6 : 0.3));
		d->cam.pos.y += FLYING_SPEED;
	}
	else if (d->keys[SDL_SCANCODE_LCTRL])
	{
		d->player.gravity -= (FLYING_SPEED * 0.5);
		d->cam.pos.y -= FLYING_SPEED;
	}
	if (d->cam.pos.y > d->floorheightplayer + d->player.minimum_height)
		d->player.is_flying -= 1;
	else
		d->player.gravity = 0.0;
	if (!d->player.is_flying)
		d->player.gravity = 0.0;
	d->cam.pos.y += d->player.gravity;
	if (!d->sectors[d->cursectnum].outdoor && d->cam.pos.y > d->ceilheightplayer - MINIMUM_CEIL_DIST)
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
