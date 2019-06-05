/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 01:12:02 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/05/26 13:46:01 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	draw_floor2(t_data *d, t_projdata *p)
{
	double	dist;
	double	left_u;
	double	right_u;
	double	left_v;
	double	right_v;

	dist = (d->cam.pos.y - p->sector->floorheight) * 2.66 /
		norm(p->y - HEIGHT * 0.5 + d->cam.y_offset, 0, HEIGHT * 0.5);
	left_u = d->cam.pos.x + p->cos * dist - p->sin * dist * 0.5;
	right_u = d->cam.pos.x + p->cos * dist + p->sin * dist * 0.5;
	left_v = d->cam.pos.z + p->sin * dist + p->cos * dist * 0.5;
	right_v = d->cam.pos.z + p->sin * dist - p->cos * dist * 0.5;
	putpixel(d, p->x, p->y, shade(dist, getpixel2(
					d->textures[p->sector->floorpicnum],
					lerp(norm(p->x, 0, WIDTH), left_u, right_u),
					lerp(norm(p->x, 0, WIDTH), left_v, right_v))));
}

void	draw_floor(t_data *d, t_projdata *p, t_frustum *fr)
{
	if ((d->cam.pos.y - p->sector->floorheight) <= 0)
		return ;
	p->sin = sin(-d->cam.rot + M_PI_2);
	p->cos = cos(-d->cam.rot + M_PI_2);
	p->x = p->cx1 - 1;
	while (++p->x <= p->cx2)
	{
		p->y = ft_max(fr->ytop[p->x], lerp(fclamp(norm(p->x,
							p->x1, p->x2), 0, 1), p->y1b, p->y2b)) - 1;
		while (++p->y <= fr->ybottom[p->x])
			draw_floor2(d, p);
	}
}
