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

void	render_sector(t_data *d, t_sector *sect, t_frustum *fr)
{
	int		i;
	double	u_begin;
	double	u_end;
	double	len1;
	double	len2;
	double	yceil;
	double	yfloor;
	double	zbuffer[WIDTH];
	t_projdata		p;
	t_projdata		pouet;
	pthread_t		thread;
	t_thread_arg	t;

	p.floor_alt[0] = (d->cam.pos.y - sect->floorheight) * 2.0 * WIDTH / HEIGHT;
	p.floor_alt[1] = (sect->ceilheight - d->cam.pos.y) * 2.0 * WIDTH / HEIGHT;
	p.sin = d->floor_sin;
	p.cos = d->floor_cos;
	i = -1;
	while (++i < HEIGHT)
		p.floor_u1[i] = 0;
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
		p.zbuffer = zbuffer;
		p.sector = sect;
		p.wall = &d->walls[wallnum];
		p.neighbor = (p.wall->neighborsect == -1) ? NULL :
			&d->sectors[p.wall->neighborsect];
		p.wall->lowerpicnum = d->walls[wallnextnum].middlepicnum;
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
		pouet = p;
		t = (t_thread_arg){d, &pouet, fr};
		if (pthread_create(&thread, NULL, draw_ceil_thread, &t))
			exit(printf("pthread_create error\n"));
		draw_floor(d, &p, fr);
		if (pthread_join(thread, NULL))
			exit(printf("pthread_join error\n"));
	}
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
