/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 22:40:33 by nallani           #+#    #+#             */
/*   Updated: 2019/05/07 21:19:47 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	render_sector(t_data *d, t_sector *sect, t_frustum *fr)
{
	double	u_begin;
	double	u_end;
	double	len1;
	double	len2;
	double	yceil;
	double	yfloor;
	double	zbuffer[WIDTH];

	for (int i = 0; i < WIDTH; i++)
		zbuffer[i] = INFINITY;
	for (int i = 0; i < sect->numwalls; i++)
	{
		int wallnum = sect->firstwallnum + i;
		int wallnextnum = sect->firstwallnum + (i + 1) % sect->numwalls;
		double x1 = d->walls[wallnum].point.x - d->cam.pos.x;
		double z1 = d->walls[wallnum].point.y - d->cam.pos.z;
		double x2 = d->walls[wallnextnum].point.x - d->cam.pos.x;
		double z2 = d->walls[wallnextnum].point.y - d->cam.pos.z;
		t_projdata p = {.zbuffer = zbuffer, .sector = sect,
			.wall = &d->walls[wallnum]};
		p.neighbor = (p.wall->neighborsect == -1) ? NULL :
			&d->sectors[p.wall->neighborsect];
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
		draw_wall(d, &p, fr);
		draw_floor(d, p, fr);
		debug_pause(d);
	}
}
