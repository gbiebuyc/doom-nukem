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

void	draw_floor2(t_data *d, int xy[2], double sincos[2], t_projdata *p)
{
	double	dist;
	double	left_u;
	double	right_u;
	double	left_v;
	double	right_v;

	dist = (d->cam.pos.y - p->sector->floorheight) * 2.66 /
		norm(xy[1] - HEIGHT * 0.5 + d->cam.y_offset, 0, HEIGHT * 0.5);
	left_u = d->cam.pos.x + sincos[1] * dist - sincos[0] * dist * 0.5;
	right_u = d->cam.pos.x + sincos[1] * dist + sincos[0] * dist * 0.5;
	left_v = d->cam.pos.z + sincos[0] * dist + sincos[1] * dist * 0.5;
	right_v = d->cam.pos.z + sincos[0] * dist - sincos[1] * dist * 0.5;
	putpixel(d, xy[0], xy[1], shade(dist, getpixel2(
					d->textures[p->sector->floorpicnum],
					lerp(norm(xy[0], 0, WIDTH), left_u, right_u),
					lerp(norm(xy[0], 0, WIDTH), left_v, right_v))));
}

void	draw_floor(t_data *d, t_projdata *p, t_frustum *fr)
{
	double	sincos[2];
	int		x;
	int		y;

	if ((d->cam.pos.y - p->sector->floorheight) <= 0)
		return ;
	sincos[0] = sin(-d->cam.rot + M_PI_2);
	sincos[1] = cos(-d->cam.rot + M_PI_2);
	x = p->cx1 - 1;
	while (++x <= p->cx2)
	{
		y = ft_max(fr->ytop[x],
				lerp(fclamp(norm(x, p->x1, p->x2), 0, 1), p->y1b, p->y2b)) - 1;
		while (++y <= fr->ybottom[x])
			draw_floor2(d, (int[2]){x, y}, sincos, p);
	}
}
