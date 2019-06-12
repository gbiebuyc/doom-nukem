/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 01:12:02 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/11 15:59:43 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	draw_floor2(t_data *d, t_projdata *p, int y, double x[2])
{
	double	dist;

	if (p->sector->slope)
		return (putpixel(d, x[0], y, 0xff0000));
	if (p->floor_u1[y] == 0)
	{
		dist = p->floor_alt[0] /
			((y - HEIGHT * 0.5 + d->cam.y_offset) / (HEIGHT * 0.5));
		p->floor_u1[y] = d->cam.pos.x + p->cos * dist - p->sin * dist * 0.5;
		p->floor_u2[y] = d->cam.pos.x + p->cos * dist + p->sin * dist * 0.5;
		p->floor_v1[y] = d->cam.pos.z + p->sin * dist + p->cos * dist * 0.5;
		p->floor_v2[y] = d->cam.pos.z + p->sin * dist - p->cos * dist * 0.5;
		p->floor_shade[y] = getshadefactor(d, p, dist);
	}
	putpixel(d, x[0], y, shade(p->floor_shade[y], getpixel2(
					d->textures[p->sector->floorpicnum],
					lerp(x[1], p->floor_u1[y], p->floor_u2[y]),
					lerp(x[1], p->floor_v1[y], p->floor_v2[y]))));
}

void	draw_floor(t_data *d, t_projdata *p, t_frustum *fr)
{
	int		x;
	int		y;
	double	xnorm;

	if (p->floor_alt[0] <= 0)
		return ;
	x = p->cx1 - 1;
	while (++x <= p->cx2)
	{
		xnorm = (double)x / WIDTH;
		y = ft_max(fr->ytop[x], lerp(fclamp(norm(x,
							p->x1, p->x2), 0, 1), p->y1b, p->y2b)) - 1;
		while (++y <= fr->ybottom[x])
			draw_floor2(d, p, y, (double[2]){x, xnorm});
	}
}
