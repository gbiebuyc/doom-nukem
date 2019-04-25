/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 22:40:33 by nallani           #+#    #+#             */
/*   Updated: 2019/04/26 18:28:41 by gbiebuyc         ###   ########.fr       */
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

	// Update current sector
	t_sector sect = d->sectors[d->cursectnum];
	for (int i = 0; i < sect.numwalls; i++)
	{
		int16_t neighborsect = d->walls[sect.firstwallnum + i].neighborsect;
		if (neighborsect != -1 && inside(d, neighborsect))
		{
			d->cursectnum = neighborsect;
			printf("You are now inside sector %d\n", neighborsect);
			break ;
		}
	}
}

void	refresh_img(t_data *d)
{
	double	left_u;
	double	right_u;
	double	len;
	double	len2;

	ft_memset(d->main_win.surface->pixels, 0,
			d->main_win.surface->w * d->main_win.surface->h * 4);
	t_sector sector = d->sectors[d->cursectnum];
	for (int i = 0; i < sector.numwalls; i++)
	{
		int wallnum = sector.firstwallnum + i;
		int wallnextnum = sector.firstwallnum + (i + 1) % sector.numwalls;
		t_vec3f left = vec2to3(d->walls[wallnum].point);
		t_vec3f right = vec2to3(d->walls[wallnextnum].point);
		apply_transform(d, &left);
		apply_transform(d, &right);
		if (left.z <= 0 && right.z <= 0)
			continue ;
		len = vec2f_length((t_vec2f){right.x - left.x, right.z - left.z});
		left_u = 0;
		right_u = 1;
		if (left.z <= 0)
		{
			if (!clip_wall(&left, right))
				continue ;
			len2 = vec2f_length((t_vec2f){right.x - left.x, right.z - left.z});
			left_u = 1.0 - len2 / len;
		}
		if (right.z <= 0)
		{
			if (!clip_wall(&right, left))
				continue ;
			len2 = vec2f_length((t_vec2f){right.x - left.x, right.z - left.z});
			right_u = len2 / len;
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
				left_u * len, right_u * len,
				d->walls[wallnum].upperpicnum, d->walls[wallnum].middlepicnum,
				d->walls[wallnum].lowerpicnum, d->walls[wallnum].flags, sector,
				sector.ceilheight - sector.floorheight
		};
		draw_wall(d, wall_clipped);
		draw_floor(d, wall_clipped);
	}
	SDL_UpdateWindowSurface(d->main_win.win);
}
