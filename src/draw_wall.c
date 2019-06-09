/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:38:27 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/06 19:41:56 by nallani          ###   ########.fr       */
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
	int		u;
	int		y;
	SDL_Surface *tex;
	double	shadefactor;

	tex = d->textures[p->wall->middlepicnum];
	u = (unsigned int)(p->u * tex->w) % tex->w;
	y = ft_max(fr->ytop[p->x], p->ya) - 1;
	if ((shadefactor = getshadefactor(d, p)) <= 0)
		while (++y <= ft_min(fr->ybottom[p->x], p->yb))
			putpixel(d, p->x, y, 0);
	else if (!p->neighbor)
		while (++y <= ft_min(fr->ybottom[p->x], p->yb))
			putpixel(d, p->x, y, shade(shadefactor, ((uint32_t*)tex->pixels)[u +
						(unsigned int)(norm(y, p->ya, p->yb) * p->y_scale *
							tex->h) % tex->h * tex->w]));
	else if (p->neighbor)
	{
		while (++y <= ft_min(fr->ybottom[p->x], p->nya))
			putpixel(d, p->x, y, shade(shadefactor, ((uint32_t*)tex->pixels)[u +
						(unsigned int)((p->wall->is_door ? norm(y, p->nya -
								p->doorheight, p->nya) : norm(y, p->ya, p->yb)
								* p->y_scale) * tex->h) % tex->h * tex->w]));
		tex = d->textures[p->wall->lowerpicnum];
		u = (unsigned int)(p->u * tex->w) % tex->w;
		y = ft_max(fr->ytop[p->x], p->nyb) - 1;
		while (++y <= ft_min(fr->ybottom[p->x], p->yb))
			putpixel(d, p->x, y, shade(shadefactor, ((uint32_t*)tex->pixels)[u +
						(unsigned int)(norm(y, p->ya, p->yb) * p->y_scale *
							tex->h) % tex->h * tex->w]));
	}
}

void	draw_wall2(t_data *d, t_projdata *p, t_frustum *fr, t_frustum *nfr)
{
	p->n = fclamp(norm(p->x, p->x1, p->x2), 0, 1);
	p->z = 1 / lerp(p->n, p->z1, p->z2);
	p->u = lerp(p->n, p->u_begin, p->u_end) * p->z;
	if (p->z >= d->zbuffer[p->x])
		return ((void)(p->visible[p->x] = false));
	if (!p->neighbor)
		d->zbuffer[p->x] = p->z;
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
		nfr->ytop[p->x] = clamp((p->sector->outdoor && p->neighbor->outdoor) ?
				0 : p->nya + 1, fr->ytop[p->x], fr->ybottom[p->x]);
		nfr->ybottom[p->x] = clamp(p->nyb, fr->ytop[p->x],
				fr->ybottom[p->x]);
		if (p->sector->outdoor && p->neighbor->outdoor)
			p->ya = p->nya;
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
