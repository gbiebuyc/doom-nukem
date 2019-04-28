/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 01:05:19 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/04/29 23:58:39 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define MOVE_SPEED 0.08
#define TURN_SPEED 0.02

void	update(t_data *d)
{
	d->cam.rot -= d->keys[SDL_SCANCODE_LEFT] * TURN_SPEED;
	d->cam.rot += d->keys[SDL_SCANCODE_RIGHT] * TURN_SPEED;
	d->cam.sin = sin(d->cam.rot);
	d->cam.cos = cos(d->cam.rot);
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

	// Update current sector
	t_sector sect = d->sectors[d->cursectnum];
	for (int i = 0; i < sect.numwalls; i++)
	{
		int16_t neighborsect = d->walls[sect.firstwallnum + i].neighborsect;
		if (neighborsect != -1 && inside(d, neighborsect))
		{
			d->cursectnum = neighborsect;
			//printf("You are now inside sector %d\n", neighborsect);
			break ;
		}
	}
}
