/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 22:40:33 by nallani           #+#    #+#             */
/*   Updated: 2019/06/06 19:37:36 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	transformvertex(t_data *d, t_vec2f v, double *x, double *z)
{
	v.x -= d->cam.pos.x;
	v.y -= d->cam.pos.z;
	*x = v.x * d->cam.cos - v.y * d->cam.sin;
	*z = v.x * d->cam.sin + v.y * d->cam.cos;
}

double	get_slope_y(t_data *d, t_projdata *p, t_vec2f wall)
{
	double x[2];
	double h;
	double slope;

	if (p->floor_or_ceil == 0)
	{
		h = p->sector->floorheight;
		slope = p->sector->slope;
	}
	else
	{
		h = p->sector->ceilheight;
		slope = p->sector->slopeceil;
	}
	h -= d->cam.pos.y;
	if (slope == 0)
		return (h);
	x[0] = d->walls[p->sector->firstwallnum].point.x;
	x[1] = wall.x * d->cam.cos + wall.y * d->cam.sin + d->cam.pos.x;
	return (h + tan(slope * M_PI / 180) * (x[1] - x[0]));
}

void	render_sector(t_data *d, t_sector *sect, t_frustum *fr)
{
	int		i;
	double	u1;
	double	u2;
	double	len1;
	double	len2;
	double	yceil;
	double	yfloor;
	t_projdata		p;
	pthread_t		thread;
	t_thread_arg	t;
	double	x1;
	double	x2;

	p.floor_alt[0] = (d->cam.pos.y - sect->floorheight) * 2.0 * WIDTH / HEIGHT;
	p.floor_alt[1] = (sect->ceilheight - d->cam.pos.y) * 2.0 * WIDTH / HEIGHT;
	p.sin = d->floor_sin;
	p.cos = d->floor_cos;
	p.sector = sect;
	p.fr = fr;
	i = -1;
	while (++i < HEIGHT)
		p.floor_u1[i] = 0;
	for (int i = 0; i < sect->numwalls; i++)
	{
		int wallnum = sect->firstwallnum + i;
		int wallnextnum = sect->firstwallnum + (i + 1) % sect->numwalls;
		transformvertex(d, d->walls[wallnum].point, &x1, &p.z1);
		transformvertex(d, d->walls[wallnextnum].point, &x2, &p.z2);
		p.wall = &d->walls[wallnum];
		p.neighbor = (p.wall->neighborsect == -1) ? NULL :
			&d->sectors[p.wall->neighborsect];
		p.wall->lowerpicnum = d->walls[wallnextnum].middlepicnum;
		if (p.z1 <= 0 && p.z2 <= 0)
			continue ;
		len1 = vec2f_length((t_vec2f){x2 - x1, p.z2 - p.z1});
		u1 = 0;
		u2 = 1;
		if (p.z1 <= 0)
		{
			if (!clip_wall(&x1, &p.z1, x2, p.z2))
				continue ;
			len2 = vec2f_length((t_vec2f){x2 - x1, p.z2 - p.z1});
			u1 = 1.0 - len2 / len1;
		}
		if (p.z2 <= 0)
		{
			if (!clip_wall(&x2, &p.z2, x1, p.z1))
				continue ;
			len2 = vec2f_length((t_vec2f){x2 - x1, p.z2 - p.z1});
			u2 = len2 / len1;
		}
		double scale1 = (1.0 / p.z1) * WIDTH;
		double scale2 = (1.0 / p.z2) * WIDTH;
		p.x1 = x1 * scale1 + WIDTH / 2;
		p.x2 = x2 * scale2 + WIDTH / 2;
		yceil = sect->ceilheight - d->cam.pos.y;
		yfloor = sect->floorheight - d->cam.pos.y;
		double y_offset = HEIGHT / 2 - d->cam.y_offset;
		p.floor_or_ceil = 1;
		p.y1a = get_slope_y(d, &p, (t_vec2f){x1, p.z1}) * -scale1 + y_offset;
		p.y2a = get_slope_y(d, &p, (t_vec2f){x2, p.z2}) * -scale2 + y_offset;
		p.floor_or_ceil = 0;
		p.y1b = get_slope_y(d, &p, (t_vec2f){x1, p.z1}) * -scale1 + y_offset;
		p.y2b = get_slope_y(d, &p, (t_vec2f){x2, p.z2}) * -scale2 + y_offset;
		p.y1c = yceil * -scale1 + y_offset;
		p.y2c = yceil * -scale2 + y_offset;
		p.y1d = yfloor * -scale1 + y_offset;
		p.y2d = yfloor * -scale2 + y_offset;
		if (p.neighbor)
		{
			p.sector = p.neighbor;
			p.floor_or_ceil = 1;
			p.ny1a = get_slope_y(d, &p, (t_vec2f){x1, p.z1})
				* -scale1 + y_offset;
			p.ny2a = get_slope_y(d, &p, (t_vec2f){x2, p.z2})
				* -scale2 + y_offset;
			p.floor_or_ceil = 0;
			p.ny1b = get_slope_y(d, &p, (t_vec2f){x1, p.z1})
				* -scale1 + y_offset;
			p.ny2b = get_slope_y(d, &p, (t_vec2f){x2, p.z2})
				* -scale2 + y_offset;
			p.sector = sect;
		}
		p.u1 = u1 * len1;
		p.u2 = u2 * len1;
		p.y_scale = sect->ceilheight - sect->floorheight;
		if (p.wall->posterpicnum >= 0)
		{
			p.u1_poster = (len1 - POSTER_W) / 2.0;
			p.u2_poster = len1 - p.u1_poster;
			p.poster_h = POSTER_W * ((double)d->textures[p.wall->posterpicnum]->h /
					d->textures[p.wall->posterpicnum]->w) / p.y_scale;
		}
		draw_wall(d, &p, fr);
		t = (t_thread_arg){d, &p, fr};
		if (pthread_create(&thread, NULL, draw_ceil_thread, &t))
			exit(printf("pthread_create error\n"));
		draw_floor(d, &p, fr);
		if (pthread_join(thread, NULL))
			exit(printf("pthread_join error\n"));
	}
	if (sect->slope || sect->slopeceil)
		draw_slope(d, &p);
	if (sect->sprite_list)
		reorder_sprite(d, sect);
	t_sprite_list *sprite_list_tmp;
	sprite_list_tmp = sect->sprite_list;
	while (sprite_list_tmp)
	{
		draw_sprite(d, sect, fr, sprite_list_tmp); // a modif;
		sprite_list_tmp = sprite_list_tmp->next;
	}
	// sector might not be protected ?
	/*		if (sect->monster_list) // probleme structuration code (appele 3x et soucis avec frustum)
			reorder_sprite(d, sect);
			t_monster_list *monster_list;
			monster_list = sect->monster_list;
			while (monster_list)
			{
			draw_sprite(d, sect, fr, d->monsters[monster_list->id]); // a modif;
			monster_list = monster_list->next;
			}
			*/}
