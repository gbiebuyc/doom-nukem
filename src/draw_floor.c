/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 01:12:02 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/29 18:20:55 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_vec3f	transform_back(t_data *d, t_vec3f v)
{
	return ((t_vec3f){v.x * d->cam.cos + v.z * d->cam.sin + d->cam.pos.x, v.y,
			v.x * -d->cam.sin + v.z * d->cam.cos + d->cam.pos.z});
}

double	edge_function(t_vec3f a, t_vec3f b, int x, int y)
{
	return (x - a.x) * (b.y - a.y) - (y - a.y) * (b.x - a.x);
}

void	proj_floor(t_data *d, t_projdata *p)
{
	double y_offset;

	p->c[0] = transform_back(d, (t_vec3f){-1, 0, 1});
	p->c[1] = transform_back(d, (t_vec3f){1, 0, 1});
	p->c[2] = transform_back(d, (t_vec3f){0, 0, 2});
	y_offset = HEIGHT / 2 - d->cam.y_offset;
	p->v[0] = (t_vec3f){-WIDTH + WIDTH / 2, get_floordh(d,
			p->sector, vec3to2(p->c[0])) * -WIDTH + y_offset, 1};
	p->v[1] = (t_vec3f){WIDTH + WIDTH / 2, get_floordh(d,
			p->sector, vec3to2(p->c[1])) * -WIDTH + y_offset, 1};
	p->v[2] = (t_vec3f){WIDTH / 2, get_floordh(d, p->sector,
			vec3to2(p->c[2])) * -WIDTH * 0.5 + y_offset, 0.5};
	p->c[2].x /= 2;
	p->c[2].z /= 2;
	p->area = edge_function(p->v[0], p->v[1], p->v[2].x, p->v[2].y);
}

void	draw_floor(t_data *d, t_projdata *p, t_frustum *fr)
{
	int		x;
	int		y;
	double	w[3];
	double	z;

	x = p->cx1 - 1;
	while (++x <= p->cx2)
	{
		y = ft_max(fr->ytop[x], lerp(fclamp(norm(x,
							p->x1, p->x2), 0, 1), p->y1b, p->y2b)) - 1;
		while (++y <= fr->ybottom[x])
		{
			w[0] = edge_function(p->v[1], p->v[2], x, y) / p->area;
			w[1] = edge_function(p->v[2], p->v[0], x, y) / p->area;
			w[2] = edge_function(p->v[0], p->v[1], x, y) / p->area;
			z = 1 / (w[0] * p->v[0].z + w[1] * p->v[1].z + w[2] * p->v[2].z);
			if (z >= d->zbuffer[x + y * WIDTH])
				continue ;
			putpixel2(d, z, (t_vec2){x, y}, shade(getshadefactor(d, p, z),
				getpixel2(d->textures[p->sector->floorpicnum],
				(w[0] * p->c[0].x + w[1] * p->c[1].x + w[2] * p->c[2].x) * z,
				(w[0] * p->c[0].z + w[1] * p->c[1].z + w[2] * p->c[2].z) * z)));
		}
	}
}
