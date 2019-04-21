/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 22:40:33 by nallani           #+#    #+#             */
/*   Updated: 2019/04/21 23:41:13 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define MOVE_SPEED 0.08
#define TURN_SPEED 0.02

void	refresh_game(t_data *d)
{
	if (d->keys.hor_turn == LEFT_TURN)
		d->cam.rot -= TURN_SPEED;
	if (d->keys.hor_turn == RIGHT_TURN)
		d->cam.rot += TURN_SPEED;
	d->cam.sin = sin(d->cam.rot);
	d->cam.cos = cos(d->cam.rot);
	if (d->keys.dir == FORWARD)
	{
		d->cam.pos.z += d->cam.cos * MOVE_SPEED;
		d->cam.pos.x += d->cam.sin * MOVE_SPEED;
	}
	if (d->keys.dir == BACKWARD)
	{
		d->cam.pos.z -= d->cam.cos * MOVE_SPEED;
		d->cam.pos.x -= d->cam.sin * MOVE_SPEED;
	}
	if (d->keys.strafe_dir == LEFT_STRAFE)
	{
		d->cam.pos.z += d->cam.sin * MOVE_SPEED;
		d->cam.pos.x -= d->cam.cos * MOVE_SPEED;
	}
	if (d->keys.strafe_dir == RIGHT_STRAFE)
	{
		d->cam.pos.z -= d->cam.sin * MOVE_SPEED;
		d->cam.pos.x += d->cam.cos * MOVE_SPEED;
	}
	if (d->keys.ver_dir == UP_FLY)
		d->cam.pos.y += MOVE_SPEED;
	if (d->keys.ver_dir == DOWN_FLY)
		d->cam.pos.y -= MOVE_SPEED;
}

#define DIST_FROM_CAMERA 1.0

void	refresh_img(t_data *d)
{
	double	left_clip;
	double	right_clip;
	double	scale_x;

	ft_memset(d->main_win.surface->pixels, 0,
			d->main_win.surface->w * d->main_win.surface->h * 4);
	t_sector sector = d->sectors[0];
	for (int i = 0; i < sector.numwalls; i++)
	{
		int wallnum = sector.firstwallnum + i;
		int wallnextnum = sector.firstwallnum + (i + 1) % sector.numwalls;
		t_vec3f left = vec2f_to_vec3f(d->walls[wallnum].point);
		t_vec3f right = vec2f_to_vec3f(d->walls[wallnextnum].point);
		apply_transform(d, &left);
		apply_transform(d, &right);
		if (left.z <= DIST_FROM_CAMERA && right.z <= DIST_FROM_CAMERA)
			continue ;
		scale_x = vec2f_length((t_vec2f){right.x - left.x, right.z - left.z}) /
			(sector.ceilheight - sector.floorheight);
		left_clip = 0;
		right_clip = 1;
		if (left.z <= DIST_FROM_CAMERA)
		{
			left_clip = (DIST_FROM_CAMERA - left.z) / (right.z - left.z);
			left.x = left.x + (right.x - left.x) * left_clip;
			left.z = DIST_FROM_CAMERA;
		}
		if (right.z <= DIST_FROM_CAMERA)
		{
			right_clip = (left.z - DIST_FROM_CAMERA) / (left.z - right.z);
			right.x = left.x + (right.x - left.x) * right_clip;
			right.z = DIST_FROM_CAMERA;
		}
		t_wall_clipped wall_clipped = (t_wall_clipped){
				apply_perspective(d, (t_vec3f){left.x,
						left.y + sector.ceilheight, left.z}),
				apply_perspective(d, (t_vec3f){right.x,
						right.y + sector.ceilheight, right.z}),
				apply_perspective(d, (t_vec3f){left.x,
						left.y + sector.floorheight, left.z}),
				apply_perspective(d, (t_vec3f){right.x,
						right.y + sector.floorheight, right.z}),
				left_clip * scale_x, right_clip * scale_x,
				d->walls[wallnum].upperpicnum, d->walls[wallnum].middlepicnum,
				d->walls[wallnum].lowerpicnum, d->walls[wallnum].flags, sector
		};
		draw_wall(d, wall_clipped);
		draw_floor(d, wall_clipped);
	}
	SDL_UpdateWindowSurface(d->main_win.win);
}
