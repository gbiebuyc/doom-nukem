/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 22:40:33 by nallani           #+#    #+#             */
/*   Updated: 2019/04/27 05:37:10 by gbiebuyc         ###   ########.fr       */
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

void	display_sector(t_data *d, t_sector *sect, t_frustum *fr)
{
	double	u_begin;
	double	u_end;
	double	len1;
	double	len2;
	double	yceil;
	double	yfloor;

	for (int i = 0; i < sect->numwalls; i++)
	{
		int wallnum = sect->firstwallnum + i;
		int wallnextnum = sect->firstwallnum + (i + 1) % sect->numwalls;
		double x1 = d->walls[wallnum].point.x - d->cam.pos.x;
		double z1 = d->walls[wallnum].point.y - d->cam.pos.z;
		double x2 = d->walls[wallnextnum].point.x - d->cam.pos.x;
		double z2 = d->walls[wallnextnum].point.y - d->cam.pos.z;
		t_projdata p;
		p.x1 = x1 * d->cam.cos - z1 * d->cam.sin;
		p.z1 = x1 * d->cam.sin + z1 * d->cam.cos;
		p.x2 = x2 * d->cam.cos - z2 * d->cam.sin;
		p.z2 = x2 * d->cam.sin + z2 * d->cam.cos;
		if (p.z1 <= 0 && p.z2 <= 0)
			continue ;
		len1 = vec2f_length((t_vec2f){p.x2 - p.x1, p.z2 - p.z1});
		u_begin = 0;
		u_end = 1;
		if (p.z1 <= 0)
		{
			if (!clip_wall(&p.x1, &p.z1, p.x2, p.z2))
				continue ;
			len2 = vec2f_length((t_vec2f){p.x2 - p.x1, p.z2 - p.z1});
			u_begin = 1.0 - len2 / len1;
		}
		if (p.z2 <= 0)
		{
			if (!clip_wall(&p.x2, &p.z2, p.x1, p.z1))
				continue ;
			len2 = vec2f_length((t_vec2f){p.x2 - p.x1, p.z2 - p.z1});
			u_end = len2 / len1;
		}
		p.wall = &d->walls[wallnum];
		p.sector = sect;
		p.neighbor = (p.wall->neighborsect == -1) ? NULL :
			&d->sectors[p.wall->neighborsect];
		double scale1 = (1.0 / p.z1) * WIDTH;
		double scale2 = (1.0 / p.z2) * WIDTH;
		p.x1 = p.x1 * scale1 + WIDTH / 2;
		p.x2 = p.x2 * scale2 + WIDTH / 2;
		yceil = sect->ceilheight - d->cam.pos.y;
		yfloor = sect->floorheight - d->cam.pos.y;
		double y_offset = HEIGHT / 2 - d->cam.y_offset;
		p.y1a = yceil * -scale1 + y_offset;
		p.y2a = yceil * -scale2 + y_offset;
		p.y1b = yfloor * -scale1 + y_offset;
		p.y2b = yfloor * -scale2 + y_offset;
		if (p.neighbor)
		{
			yceil = p.neighbor->ceilheight - d->cam.pos.y;
			yfloor = p.neighbor->floorheight - d->cam.pos.y;
			p.ny1a = yceil * -scale1 + y_offset;
			p.ny2a = yceil * -scale2 + y_offset;
			p.ny1b = yfloor * -scale1 + y_offset;
			p.ny2b = yfloor * -scale2 + y_offset;
		}
		p.u_begin = u_begin * len1;
		p.u_end = u_end * len1;
		p.y_scale = sect->ceilheight - sect->floorheight;
		draw_floor(d, p, fr);
		draw_wall(d, p, fr);
	}
}

void	refresh_img(t_data *d)
{
	ft_memset(d->main_win.surface->pixels, 0,
			d->main_win.surface->w * d->main_win.surface->h * 4);
	t_frustum fr;
	fr.x1 = 0;
	fr.x2 = WIDTH - 1;
	for(int x = 0; x < WIDTH; ++x)
	{
		fr.ytop[x] = 0;
		fr.ybottom[x] = HEIGHT-1;
	}
	display_sector(d, &d->sectors[d->cursectnum], &fr);
	SDL_UpdateWindowSurface(d->main_win.win);
}
