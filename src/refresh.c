/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 22:40:33 by nallani           #+#    #+#             */
/*   Updated: 2019/04/08 19:55:29 by gbiebuyc         ###   ########.fr       */
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
	ft_memset(d->main_win.surface->pixels, 0,
			d->main_win.surface->w * d->main_win.surface->h * 4);
	int i = 0;
	while (i < 4)
	{
		t_wall new;
		new = (t_wall){
			get_projected_vertex(d, d->walls[i].a),
			get_projected_vertex(d, d->walls[i].b),
			get_projected_vertex(d, d->walls[i].c),
			get_projected_vertex(d, d->walls[i].d)
		};
		putpixel(d, new.a.x, new.a.y, 0xffffff);
		putpixel(d, new.b.x, new.b.y, 0xffffff);
		putpixel(d, new.c.x, new.c.y, 0xffffff);
		putpixel(d, new.d.x, new.d.y, 0xffffff);
		draw_wall(d, new);
		i++;
	}
	SDL_UpdateWindowSurface(d->main_win.win);
}
