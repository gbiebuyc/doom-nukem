/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:38:27 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/05/30 18:16:14 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	draw_wall3(t_data *d, t_projdata *p, t_frustum *nfr, bool *visible)
{
	int	end;

	if (p->cx2 - p->cx1 <= 2)
		return ;
	end = p->cx2;
	while (!visible[p->cx1] && p->cx1 < end)
		(p->cx1)++;
	p->cx2--;
	if (p->cx1 >= end)
		return ;
	p->cx2 = p->cx1;
	while (visible[p->cx2] && p->cx2 < end)
		p->cx2++;
	if (p->neighbor && p->cx1 < p->cx2)
	{
		nfr->x1 = p->cx1;
		nfr->x2 = p->cx2;
		render_sector(d, p->neighbor, nfr);
	}
}

void	draw_wall2bis(t_data *d, t_projdata *p, t_frustum *fr)
{
	double	v;
	int		y;

	y = ft_max(fr->ytop[p->x], p->ya) - 1;
	while (++y <= ft_min(fr->ybottom[p->x], p->yb))
	{
		v = (p->wall->is_door && y < p->nya) ?
			norm(y, p->nya - p->doorheight, p->nya) :
			lerp(norm(y, p->ya, p->yb), 0, p->y_scale);
		if (p->neighbor && y < p->nya)
			putpixel(d, p->x, y, shade(p->z, getpixel2(
							d->textures[p->wall->middlepicnum], p->u, v)));
		else if (p->neighbor && y > p->nyb)
			putpixel(d, p->x, y, shade(p->z, getpixel2(
							d->textures[p->wall->lowerpicnum], p->u, v)));
		else if (!p->neighbor)
			putpixel(d, p->x, y, shade(p->z, getpixel2(
							d->textures[p->wall->middlepicnum], p->u, v)));
	}
}

void	draw_wall2(t_data *d, t_projdata *p, t_frustum *fr, t_frustum *nfr)
{
	p->n = fclamp(norm(p->x, p->x1, p->x2), 0, 1);
	p->z = 1 / lerp(p->n, p->z1, p->z2);
	p->u = lerp(p->n, p->u_begin, p->u_end) * p->z;
	if (p->z >= p->zbuffer[p->x])
		return ((void)(p->visible[p->x] = false));
	p->zbuffer[p->x] = p->z;
	p->visible[p->x] = true;
	p->ya = lerp(p->n, p->y1a, p->y2a);
	p->yb = lerp(p->n, p->y1b, p->y2b);
	if (p->neighbor)
	{
		p->nya = ft_max(lerp(p->n, p->ny1a, p->ny2a), p->ya);
		p->nyb = ft_min(lerp(p->n, p->ny1b, p->ny2b), p->yb);
		p->doorbottom = ft_min(p->yb, p->nyb);
		p->doorheight = p->doorbottom - p->ya;
		p->nya += (p->doorbottom - ft_max(p->ya, p->nya)) *
			(1 - d->doorstate[p->wall - d->walls]);
		nfr->ytop[p->x] = clamp(p->nya + 1, fr->ytop[p->x], fr->ybottom[p->x]);
		nfr->ybottom[p->x] = clamp(p->nyb, fr->ytop[p->x],
				fr->ybottom[p->x]);
	}
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
	p->u_begin /= p->z1;
	p->u_end /= p->z2;
	p->z1 = 1 / p->z1;
	p->z2 = 1 / p->z2;
	p->cx1 = ft_max(p->x1, fr->x1);
	p->cx2 = ft_min(p->x2, fr->x2);
	p->x = p->cx1 - 1;
	while (++p->x <= p->cx2)
		draw_wall2(d, p, fr, &nfr);
	draw_wall3(d, p, &nfr, p->visible);
}
