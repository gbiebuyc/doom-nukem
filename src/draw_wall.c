/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:38:27 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/04/27 06:11:06 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	draw_wall(t_data *d, t_projdata p, t_frustum *fr)
{
	t_frustum	nfr;
	int			nya;
	int			nyb;

	p.u_begin /= p.z1;
	p.u_end /= p.z2;
	p.z1 = 1 / p.z1;
	p.z2 = 1 / p.z2;
	int beginx = ft_max(p.x1, fr->x1);
	int endx = ft_min(p.x2, fr->x2);
	for (int x = beginx; x <= endx; x++)
	{
		double n = norm(x, p.x1, p.x2);
		n = fclamp(n, 0, 1);
		double z = 1 / lerp(n, p.z1, p.z2);
		double u = lerp(n, p.u_begin, p.u_end) * z;

		int ya = lerp(n, p.y1a, p.y2a);
		int yb = lerp(n, p.y1b, p.y2b);
		if (p.neighbor)
		{
			nya = ft_max(lerp(n, p.ny1a, p.ny2a), ya);
			nyb = ft_min(lerp(n, p.ny1b, p.ny2b), yb);
			nfr.ytop[x] = clamp(nya, fr->ytop[x], fr->ybottom[x]);
			nfr.ybottom[x] = clamp(nyb, fr->ytop[x], fr->ybottom[x]);
		}
		for (int y = ft_max(fr->ytop[x], ya);
				y <= ft_min(fr->ybottom[x], yb); y++)
		{
			double v = lerp(norm(y, ya, yb), 0, p.y_scale);
			if (p.neighbor && y < nya)
				putpixel(d, x, y, getpixel2(
							d->texture[p.wall->lowerpicnum], u, v));
			else if (p.neighbor && y > nyb)
				putpixel(d, x, y, getpixel2(
							d->texture[p.wall->lowerpicnum], u, v));
			else if (!p.neighbor)
				putpixel(d, x, y, getpixel2(
							d->texture[p.wall->middlepicnum], u, v));
		}
	}
	if (p.neighbor && beginx < endx)
	{
		nfr.x1 = beginx;
		nfr.x2 = endx;
		// recursive call
		display_sector(d, p.neighbor, &nfr);
	}
}

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
			putpixel(d, x, y, getpixel2(d->texture[p.sector->floorpicnum],
						u * scale, v * scale));
		}
	}
}
