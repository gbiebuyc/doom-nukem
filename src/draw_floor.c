/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 01:12:02 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/06 19:42:29 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	draw_floor2(t_data *d, t_projdata *p, int y)
{
	if (p->floor_u1[y] == 0)
	{
		p->z = p->floor_alt[0] /
			((y - HEIGHT * 0.5 + d->cam.y_offset) / (HEIGHT * 0.5));
		p->floor_u1[y] = d->cam.pos.x + p->cos * p->z - p->sin * p->z * 0.5;
		p->floor_u2[y] = d->cam.pos.x + p->cos * p->z + p->sin * p->z * 0.5;
		p->floor_v1[y] = d->cam.pos.z + p->sin * p->z + p->cos * p->z * 0.5;
		p->floor_v2[y] = d->cam.pos.z + p->sin * p->z - p->cos * p->z * 0.5;
		p->floor_shade[y] = getshadefactor(d, p);
	}
	putpixel(d, p->x, y, shade(p->floor_shade[y], getpixel2(
					d->textures[p->sector->floorpicnum],
					lerp(p->xnorm, p->floor_u1[y], p->floor_u2[y]),
					lerp(p->xnorm, p->floor_v1[y], p->floor_v2[y]))));
}

void	draw_floor(t_data *d, t_projdata *p, t_frustum *fr)
{
	if (p->floor_alt[0] <= 0)
		return ;
	p->x = p->cx1 - 1;
	while (++p->x <= p->cx2)
	{
		p->xnorm = (double)p->x / WIDTH;
		p->y = ft_max(fr->ytop[p->x], lerp(fclamp(norm(p->x,
							p->x1, p->x2), 0, 1), p->y1b, p->y2b)) - 1;
		while (++p->y <= fr->ybottom[p->x])
			draw_floor2(d, p, p->y);
	}
}
