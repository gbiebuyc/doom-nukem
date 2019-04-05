/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 22:40:33 by nallani           #+#    #+#             */
/*   Updated: 2019/04/05 17:39:57 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define MOVE_SPEED 0.08
#define TURN_SPEED 0.02

void	refresh_game(t_data *d)
{
	if (d->keys.hor_turn == LEFT_TURN)
		d->cam.rot.y -= TURN_SPEED;
	if (d->keys.hor_turn == RIGHT_TURN)
		d->cam.rot.y += TURN_SPEED;
	d->cam.sin_x = sin(d->cam.rot.x);
	d->cam.cos_x = cos(d->cam.rot.x);
	d->cam.sin_y = sin(d->cam.rot.y);
	d->cam.cos_y = cos(d->cam.rot.y);
	if (d->keys.dir == FORWARD)
	{
		d->cam.pos.z += d->cam.cos_y * MOVE_SPEED;
		d->cam.pos.x += d->cam.sin_y * MOVE_SPEED;
	}
	if (d->keys.dir == BACKWARD)
	{
		d->cam.pos.z -= d->cam.cos_y * MOVE_SPEED;
		d->cam.pos.x -= d->cam.sin_y * MOVE_SPEED;
	}
	if (d->keys.strafe_dir == LEFT_STRAFE)
	{
		d->cam.pos.z += d->cam.sin_y * MOVE_SPEED;
		d->cam.pos.x -= d->cam.cos_y * MOVE_SPEED;
	}
	if (d->keys.strafe_dir == RIGHT_STRAFE)
	{
		d->cam.pos.z -= d->cam.sin_y * MOVE_SPEED;
		d->cam.pos.x += d->cam.cos_y * MOVE_SPEED;
	}
	if (d->keys.ver_dir == UP_FLY)
		d->cam.pos.y += MOVE_SPEED;
	if (d->keys.ver_dir == DOWN_FLY)
		d->cam.pos.y -= MOVE_SPEED;
}

void	refresh_img(t_data *d)
{	
	//	main_raycast_multithread(d, 0, 0);
	square(d);
	SDL_UpdateWindowSurface(d->main_win.win);
}
