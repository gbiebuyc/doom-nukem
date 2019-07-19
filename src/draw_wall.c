/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:38:27 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/28 17:03:50 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	draw_wall_nei(t_data *d, t_projdata *p, t_frustum *fr)
{
	while (++p->y <= ft_min(fr->ybottom[p->x], p->nya))
		putpixel2(d, p->z, (t_vec2){p->x, p->y},
			shade(p->shadefactor, getpixel4(p->tex, p->u_tex, p->wall->is_door ?
				norm(p->y, p->nya - p->doorheight, p->nya) :
				norm(p->y, p->yc, p->yd) * p->y_scale)));
	p->tex = d->textures[p->wall->lowerpicnum];
	p->u_tex = (p->u - floor(p->u)) * p->tex->w;
	p->y = ft_max(fr->ytop[p->x], p->nyb) - 1;
	while (++p->y <= ft_min(fr->ybottom[p->x], p->yb))
		putpixel2(d, p->z, (t_vec2){p->x, p->y}, shade(p->shadefactor,
			getpixel4(p->tex, p->u_tex,
				norm(p->y, p->yc, p->yd) * p->y_scale)));
}

void	draw_wall2bis(t_data *d, t_projdata *p, t_frustum *fr)
{
	p->ya_poster = 0;
	p->yb_poster = 0;
	if (p->wall->posterpicnum >= 0 && p->u > p->u1_poster &&
			p->u < p->u2_poster)
	{
		p->poster = d->posters[p->wall->posterpicnum];
		p->u_poster = (unsigned int)(norm(p->u, p->u1_poster, p->u2_poster) *
				p->poster->w) % p->poster->w;
		p->margin = (double)(p->yd - p->yc) * (1.0 - p->poster_h) / 2.0;
		p->ya_poster = p->yc + p->margin;
		p->yb_poster = p->yd - p->margin;
	}
	p->tex = d->textures[p->wall->middlepicnum];
	p->u_tex = (p->u - floor(p->u)) * p->tex->w;
	p->y = ft_max(fr->ytop[p->x], p->ya) - 1;
	p->shadefactor = getshadefactor(d, p, p->z);
	if (!p->neighbor)
		draw_wall_no_nei(d, p, fr);
	else if (p->neighbor)
		draw_wall_nei(d, p, fr);
}

void	draw_wall4(t_data *d, t_projdata *p, t_frustum *fr, t_frustum *nfr)
{
	p->nya = lerp(p->n, p->ny1a, p->ny2a);
	p->nyb = lerp(p->n, p->ny1b, p->ny2b);
	if (p->wall->is_door)
	{
		p->nya = ft_max(p->nya, p->ya);
		p->nyb = ft_min(p->nyb, p->yb);
	}
	p->doorbottom = ft_min(p->yb, p->nyb);
	p->doorheight = p->doorbottom - p->yc;
	p->nya += (p->doorbottom - ft_max(p->yc, p->nya)) *
		(1 - d->doorstate[p->wall - d->walls]);
	nfr->ytop[p->x] = clamp((p->sector->outdoor && p->neighbor->outdoor) ?
			0 : p->nya + 1, fr->ytop[p->x], fr->ybottom[p->x]);
	nfr->ybottom[p->x] = clamp(p->nyb, fr->ytop[p->x],
			fr->ybottom[p->x]);
	if (p->sector->outdoor && p->neighbor->outdoor)
		p->ya = p->nya;
}

void	draw_wall2(t_data *d, t_projdata *p, t_frustum *fr, t_frustum *nfr)
{
	p->n = fclamp(norm(p->x, p->x1, p->x2), 0, 1);
	p->z = 1 / lerp(p->n, p->z1, p->z2);
	p->u = lerp(p->n, p->u1, p->u2) * p->z;
	if (p->z >= p->zbuffer[p->x])
		return ((void)(p->visible[p->x] = false));
	p->zbuffer[p->x] = p->z;
	p->visible[p->x] = true;
	p->ya = lerp(p->n, p->y1a, p->y2a);
	p->yb = lerp(p->n, p->y1b, p->y2b);
	p->yc = lerp(p->n, p->y1c, p->y2c);
	p->yd = lerp(p->n, p->y1d, p->y2d);
	if (p->neighbor)
		draw_wall4(d, p, fr, nfr);
	draw_wall2bis(d, p, fr);
}

void	draw_wall(t_data *d, t_projdata *p, t_frustum *fr)
{
	t_frustum	nfr;

	if (p->neighbor && fr->visitedportals[p->wall - d->walls])
		return ;
	if (p->neighbor)
	{
		nfr = *fr;
		nfr.visitedportals[p->wall - d->walls] = true;
	}
	p->u1 /= p->z1;
	p->u2 /= p->z2;
	p->z1 = 1 / p->z1;
	p->z2 = 1 / p->z2;
	p->cx1 = ft_max(p->x1, fr->x1);
	p->cx2 = ft_min(p->x2, fr->x2);
	p->x = p->cx1 - 1;
	while (++p->x <= p->cx2)
		draw_wall2(d, p, fr, &nfr);
	draw_wall3(d, p, &nfr, p->visible);
	if (p->neighbor && p->wall->is_transparent)
	{
		p->x = ft_max(p->x1, nfr.x1);
		while (++p->x <= ft_min(p->x2, nfr.x2))
			draw_wall_transparent(d, p, &nfr);
	}
}
