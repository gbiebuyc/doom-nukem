/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 01:12:02 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/05/07 03:55:36 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	draw_floor(t_data *d, t_projdata p, t_frustum *fr)
{
	double n;

	double altitude = d->cam.pos.y - p.sector->floorheight;
	if (altitude <= 0)
		return ;
	altitude *= 2.7;
	double angle = -d->cam.rot + M_PI_2;
	for (int x = ft_max(fr->x1, p.x1);
			x <= ft_min(fr->x2, p.x2); x++)
	{
		n = norm(x, p.x1, p.x2);
		double y_start = lerp(n, p.y1b, p.y2b);
		for (int y = ft_max(fr->ytop[x], y_start); y <= fr->ybottom[x]; y++)
		{
			n = norm(y - HEIGHT / 2 + d->cam.y_offset, 0, HEIGHT / 2);
			double distance = altitude / n;
			double line_du = sin(angle) * distance;
			double line_dv = -cos(angle) * distance;
			double left_u = d->cam.pos.x + distance * cos(angle) - line_du / 2;
			double right_u = left_u + line_du;
			double left_v = d->cam.pos.z + distance * sin(angle) - line_dv / 2;
			double right_v = left_v + line_dv;

			n = norm(x, 0, WIDTH);
			double u = lerp(n, left_u, right_u);
			double v = lerp(n, left_v, right_v);
			double scale = 1;
			putpixel(d, x, y, shade(distance, getpixel2(d->textures
							[p.sector->floorpicnum], u * scale, v * scale)));
		}
	}
}
