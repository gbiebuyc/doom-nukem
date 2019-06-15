/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_slope.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/16 00:55:16 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/16 00:55:16 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	putpixelslope(t_data *d, t_projdata *p, int x, int y)
{
	if (x >= p->fr->x1 && x <= p->fr->x2 && y >= p->slopetop[x] &&
			y >= p->fr->ytop[x] && y <= p->fr->ybottom[x])
		((uint32_t*)d->screen->pixels)[x + y * WIDTH] = p->slope_col;
}

void	draw_line(t_data *d, t_projdata *p, t_vec2f v1, t_vec2f v2)
{
	t_vec2	delta;
	int		steps;
	t_vec2f	increment;

	delta.x = v2.x - v1.x;
	delta.y = v2.y - v1.y;
	steps = (abs(delta.x) > abs(delta.y)) ? abs(delta.x) : abs(delta.y);
	increment.x = delta.x / (double)steps;
	increment.y = delta.y / (double)steps;
	while (steps--)
	{
		putpixelslope(d, p, (int)v1.x, (int)v1.y);
		v1 = add_vec2f(v1, increment);
	}
}

#define CLIPDIST 0.1

void	clip_line(t_vec3f v, double *x, double *y, double *z)
{
	double ratio = (v.z - CLIPDIST) / (v.z - *z);
	*x = v.x - (v.x - *x) * ratio;
	*y = v.y - (v.y - *y) * ratio;
	*z = CLIPDIST;
}

void	proj_line(t_data *d, t_vec2f p1, t_vec2f p2, t_projdata *p)
{
	double x1, x2, z1, z2, y1, y2;
	transformvertex(d, p1, &x1, &z1);
	transformvertex(d, p2, &x2, &z2);
	double yfloor = p->sector->floorheight - d->cam.pos.y;
	y1 = yfloor + get_floor_slope_dy(d, p->sector, (t_vec2f){x1, z1});
	y2 = yfloor + get_floor_slope_dy(d, p->sector, (t_vec2f){x2, z2});
	if (z1 < CLIPDIST && z2 < CLIPDIST)
		return ;
	if (z1 < CLIPDIST)
		clip_line((t_vec3f){x2, y2, z2}, &x1, &y1, &z1);
	if (z2 < CLIPDIST)
		clip_line((t_vec3f){x1, y1, z1}, &x2, &y2, &z2);
	double scale1 = (1.0 / z1) * WIDTH;
	double scale2 = (1.0 / z2) * WIDTH;
	int sx1, sx2, sy1, sy2;
	sx1 = x1 * scale1 + WIDTH / 2;
	sx2 = x2 * scale2 + WIDTH / 2;
	double y_offset = HEIGHT / 2 - d->cam.y_offset;
	sy1 = y1 * -scale1 + y_offset;
	sy2 = y2 * -scale2 + y_offset;
	if (sx1 < 0 && sx2 < 0)
		return ;
	if (sx1 < 0)
	{
		sy1 = sy2 + (sy1 - sy2) * ((double)sx2 / (sx2 - sx1));
		sx1 = 0;
	}
	if (sx2 < 0)
	{
		sy2 = sy1 + (sy2 - sy1) * ((double)sx1 / (sx1 - sx2));
		sx2 = 0;
	}
	if (sx1 >= WIDTH && sx2 >= WIDTH)
		return ;
	if (sx1 >= WIDTH)
	{
		sy1 = sy2 + (sy1 - sy2) * (((double)sx2 - WIDTH) / (sx2 - sx1));
		sx1 = WIDTH;
	}
	if (sx2 >= WIDTH)
	{
		sy2 = sy1 + (sy2 - sy1) * (((double)sx1 - WIDTH) / (sx1 - sx2));
		sx2 = WIDTH;
	}
	draw_line(d, p, (t_vec2f){sx1, sy1}, (t_vec2f){sx2, sy2});
}

void	clear_slope(t_data *d, t_projdata *p, uint32_t c)
{
	int x;
	int y;

	x = p->fr->x1 - 1;
	while (++x <= p->fr->x2)
	{
		y = ft_max(p->slopetop[x], p->fr->ytop[x]) - 1;
		while (++y < p->fr->ybottom[x])
			((uint32_t*)d->screen->pixels)[x + y * WIDTH] = c;
	}
}

void	draw_slope(t_data *d, t_projdata *p)
{
	double	xmin, xmax, ymin, ymax, xavg, yavg;

	int i = p->sector->firstwallnum - 1;
	xmin = 999;
	xmax = -999;
	ymin = 999;
	ymax = -999;
	xavg = 0;
	yavg = 0;
	while (++i < p->sector->firstwallnum + p->sector->numwalls)
	{
		xmin = fmin(xmin, d->walls[i].point.x);
		xmax = fmax(xmax, d->walls[i].point.x);
		ymin = fmin(ymin, d->walls[i].point.y);
		ymax = fmax(ymax, d->walls[i].point.y);
		xavg += d->walls[i].point.x;
		yavg += d->walls[i].point.y;
	}
	xavg /= p->sector->numwalls;
	yavg /= p->sector->numwalls;
	double dist = vec2f_length(
			(t_vec2f){xavg - d->cam.pos.x, yavg - d->cam.pos.z});
	double shadefactor = getshadefactor(d, p, dist);
	p->slope_col = shade(shadefactor, 0x505050);
	clear_slope(d, p, shade(shadefactor, 0x707070));
	double x, y;
	x = xmin;
	while ((x += .5) < xmax)
		proj_line(d, (t_vec2f){x, -999}, (t_vec2f){x, 999}, p);
	y = ymin;
	while ((y += .5) < ymax)
		proj_line(d, (t_vec2f){-999, y}, (t_vec2f){999, y}, p);
}
