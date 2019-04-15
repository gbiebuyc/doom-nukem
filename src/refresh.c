/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 22:40:33 by nallani           #+#    #+#             */
/*   Updated: 2019/04/15 05:07:34 by gbiebuyc         ###   ########.fr       */
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

#define DIST_FROM_CAMERA 1

void	refresh_img(t_data *d)
{	
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
		// Clipping
		if (left.z <= DIST_FROM_CAMERA && right.z <= DIST_FROM_CAMERA)
			continue ;
		if (left.z <= DIST_FROM_CAMERA || right.z <= DIST_FROM_CAMERA)
		{
			double shortened = (DIST_FROM_CAMERA - left.z) / (right.z - left.z);
			if (left.z < DIST_FROM_CAMERA)
			{
				left = (t_vec3f){
					left.x + (right.x - left.x) * shortened,
						left.y + (right.y - left.y) * shortened,
						DIST_FROM_CAMERA};
			}
			else
			{
				right = (t_vec3f){
					left.x + (right.x - left.x) * shortened,
						left.y + (right.y - left.y) * shortened,
						DIST_FROM_CAMERA};
			}
		}
		draw_wall(d, left, right,
				(uint32_t[]){0xf4f442, 0xf44141,
				0x4164f4, 0x64f441}[d->walls[wallnum].middlepicnum]);
	}
	SDL_UpdateWindowSurface(d->main_win.win);
}
