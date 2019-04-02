/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 22:40:33 by nallani           #+#    #+#             */
/*   Updated: 2019/04/02 19:32:53 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define MOVE_SPEED 0.08
#define TURN_SPEED 0.02

void	refresh_game(t_data *d)
{
	if (d->keys.dir || d->keys.strafe_dir)
	{
		t_vec2f newpos = (t_vec2f){d->camera.pos.x, d->camera.pos.z};
		if (d->keys.dir == FORWARD)
			newpos = add_vec2f(newpos,
					mul_vec2f((t_vec2f){d->camera.dir.x, d->camera.dir.z}, MOVE_SPEED));
		if (d->keys.dir == BACKWARD)
			newpos = add_vec2f(newpos,
					mul_vec2f((t_vec2f){d->camera.dir.x, d->camera.dir.z}, -MOVE_SPEED));
		if (d->keys.strafe_dir == LEFT_STRAFE)
		{
			t_vec2f dirtmp = (t_vec2f){d->camera.dir.x, d->camera.dir.z};
			actualize_dir(M_PI_2, &dirtmp);
			newpos = add_vec2f(newpos, mul_vec2f(dirtmp, MOVE_SPEED));
		}
		if (d->keys.strafe_dir == RIGHT_STRAFE)
		{
			t_vec2f dirtmp = (t_vec2f){d->camera.dir.x, d->camera.dir.z};
			actualize_dir(-M_PI_2, &dirtmp);
			newpos = add_vec2f(newpos, mul_vec2f(dirtmp, MOVE_SPEED));
		}
		d->camera.pos = (t_vec3f){newpos.x, d->camera.pos.y, newpos.y};
	}
	if (d->keys.hor_turn)
	{
		t_vec2f newrot = (t_vec2f){d->camera.dir.x, d->camera.dir.z};
		if (d->keys.hor_turn == LEFT_TURN)
			actualize_dir(TURN_SPEED, &newrot);
		if (d->keys.hor_turn == RIGHT_TURN)
			actualize_dir(-TURN_SPEED, &newrot);
		d->camera.dir = (t_vec3f){newrot.x, d->camera.dir.y, newrot.y};
	}
	if (d->keys.ver_dir == UP_FLY)
		d->camera.pos.y += MOVE_SPEED;
	if (d->keys.ver_dir == DOWN_FLY)
		d->camera.pos.y -= MOVE_SPEED;
}

void	refresh_img(t_data *d)
{	
	//	main_raycast_multithread(d, 0, 0);
	square(d);
	SDL_UpdateWindowSurface(d->main_win.win);
}
