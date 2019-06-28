/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 22:40:33 by nallani           #+#    #+#             */
/*   Updated: 2019/06/28 16:49:11 by nallani          ###   ########.fr       */
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

void	render_wall(t_data *d, t_projdata *p, t_frustum *fr, int i)
{
	int wallnum;
	int wallnextnum;

	wallnum = p->sector->firstwallnum + i;
	wallnextnum = p->sector->firstwallnum + (i + 1) % p->sector->numwalls;
	transformvertex(d, d->walls[wallnum].point, &p->x1, &p->z1);
	transformvertex(d, d->walls[wallnextnum].point, &p->x2, &p->z2);
	p->wall = &d->walls[wallnum];
	p->neighbor = (p->wall->neighborsect == -1) ? NULL :
		&d->sectors[p->wall->neighborsect];
	p->wall->lowerpicnum = d->walls[wallnextnum].middlepicnum;
	p->len = vec2f_length((t_vec2f){p->x2 - p->x1, p->z2 - p->z1});
	p->u1 = 0;
	p->u2 = p->len;
	if ((p->z1 <= 0 && p->z2 <= 0) || ((p->z1 <= 0) &&
			!(clip_wall(&p->x1, &p->z1, p->x2, p->z2) && (p->u1 = p->u2 -
			vec2f_length((t_vec2f){p->x2 - p->x1, p->z2 - p->z1})))) ||
			((p->z2 <= 0) && !(clip_wall(&p->x2, &p->z2, p->x1, p->z1) &&
			(p->u2 = vec2f_length((t_vec2f){p->x2 - p->x1, p->z2 - p->z1})))))
		return ;
	proj_wall(d, p, fr, (t_vec2f[2]){
			vec3to2(transform_back(d, (t_vec3f){p->x1, 0, p->z1})),
			vec3to2(transform_back(d, (t_vec3f){p->x2, 0, p->z2}))});
}

void	render_sector(t_data *d, t_sector *sect, t_frustum *fr)
{
	t_sprite_list	*sprite_list_tmp;
	t_projdata		p;
	int				i;

	p.sector = sect;
	proj_floor(d, &p);
	proj_ceil(d, &p);
	i = -1;
	while (++i < WIDTH)
		p.zbuffer[i] = INFINITY;
	i = -1;
	while (++i < sect->numwalls)
		render_wall(d, &p, fr, i);
	if (sect->sprite_list)
		reorder_sprite(d, sect);
	sprite_list_tmp = sect->sprite_list;
	while (sprite_list_tmp)
	{
		draw_sprite(d, sect, fr, sprite_list_tmp);
		sprite_list_tmp = sprite_list_tmp->next;
	}
	draw_assets(d, &p, fr, sect - d->sectors);
}
