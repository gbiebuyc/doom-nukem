/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 22:04:53 by nallani           #+#    #+#             */
/*   Updated: 2019/05/07 00:54:14 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define MOVE_SPEED 0.08

void	collision(t_data *d)
{
	t_vec3f old_pos;

	old_pos = d->cam.pos;
	// apply movement
	// check if still inside
	// if not check collision with wall corresponding to new sector or all -1
	// if possible keep newpos
	// else find collision with wall to get point
	// apply vector -90degree from orientation of wall with distance of min_collision from the intersection point from old_pos+movement and wall
	// PROBLEM : what if to close to a wall
}

void	movement(t_data *d)
{
	if (d->keys[SDL_SCANCODE_W])
	{
		d->cam.pos.z += d->cam.cos * MOVE_SPEED;
		d->cam.pos.x += d->cam.sin * MOVE_SPEED;
	}
	if (d->keys[SDL_SCANCODE_S])
	{
		d->cam.pos.z -= d->cam.cos * MOVE_SPEED;
		d->cam.pos.x -= d->cam.sin * MOVE_SPEED;
	}
	if (d->keys[SDL_SCANCODE_A])
	{
		d->cam.pos.z += d->cam.sin * MOVE_SPEED;
		d->cam.pos.x -= d->cam.cos * MOVE_SPEED;
	}
	if (d->keys[SDL_SCANCODE_D])
	{
		d->cam.pos.z -= d->cam.sin * MOVE_SPEED;
		d->cam.pos.x += d->cam.cos * MOVE_SPEED;
	}
	d->cam.pos.y += d->keys[SDL_SCANCODE_SPACE] * MOVE_SPEED;
	d->cam.pos.y -= d->keys[SDL_SCANCODE_LSHIFT] * MOVE_SPEED;
}
