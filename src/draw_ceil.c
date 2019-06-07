/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceil.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 13:56:00 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/05/26 14:25:43 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#define RATIO (2.0 * WIDTH / HEIGHT)

void	draw_sky(t_data *d, t_projdata *p)
{
	int	h;

	h = HEIGHT + MAX_Y_OFFSET * 2;
	putpixel(d, p->x, p->y, getpixel2(d->textures[p->sector->ceilpicnum],
				((double)p->x + d->cam.rot * 1000) / (WIDTH * (h / HEIGHT)),
				((double)p->y + d->cam.y_offset + MAX_Y_OFFSET) / h));
}

void	draw_ceil2(t_data *d, t_projdata *p)
{
	double	dist;
	double	left_u;
	double	right_u;
	double	left_v;
	double	right_v;

	dist = p->altitude /
		-((p->y - HEIGHT * 0.5 + d->cam.y_offset) / (HEIGHT * 0.5));
	left_u = d->cam.pos.x + p->cos * dist - p->sin * dist * 0.5;
	right_u = d->cam.pos.x + p->cos * dist + p->sin * dist * 0.5;
	left_v = d->cam.pos.z + p->sin * dist + p->cos * dist * 0.5;
	right_v = d->cam.pos.z + p->sin * dist - p->cos * dist * 0.5;
	p->z = dist;
	putpixel(d, p->x, p->y, shade(getshadefactor(d, p), getpixel2(
					d->textures[p->sector->ceilpicnum],
					lerp(norm(p->x, 0, WIDTH), left_u, right_u),
					lerp(norm(p->x, 0, WIDTH), left_v, right_v))));
}

void	draw_ceil(t_data *d, t_projdata *p, t_frustum *fr)
{
	if (!p->sector->outdoor && (p->altitude =
				(p->sector->ceilheight - d->cam.pos.y) * RATIO) <= 0)
		return ;
	if (p->sector->outdoor && p->neighbor && p->neighbor->outdoor)
		return ;
	p->sin = sin(-d->cam.rot + M_PI_2);
	p->cos = cos(-d->cam.rot + M_PI_2);
	p->x = p->cx1 - 1;
	while (++p->x <= p->cx2)
	{
		p->y = ft_min(fr->ybottom[p->x], lerp(fclamp(norm(p->x,
							p->x1, p->x2), 0, 1), p->y1a, p->y2a)) + 1;
		while (--p->y >= fr->ytop[p->x])
			(p->sector->outdoor) ? draw_sky(d, p) :
				draw_ceil2(d, p);
	}
}
