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
	SDL_Surface *poster;
	int		u_poster;
	int		ya_poster;
	int		yb_poster;
	double	shadefactor;

	ya_poster = 0;
	yb_poster = 0;
	u_poster = 0;
	poster = 0;
	if (p->wall->posterpicnum >= 0 && p->u > p->u1_poster &&
			p->u < p->u2_poster)
	{
		poster = d->textures[p->wall->posterpicnum];
		u_poster = (unsigned int)(norm(p->u, p->u1_poster, p->u2_poster) *
				poster->w) % poster->w;
		int	margin = (double)(p->yd - p->yc) * (1.0 - p->poster_h) / 2.0;
		ya_poster = p->yc + margin;
		yb_poster = p->yd - margin;
	}
	tex = d->textures[p->wall->middlepicnum];
	u = (unsigned int)(p->u * tex->w) % tex->w;
	y = ft_max(fr->ytop[p->x], p->ya);
	if ((shadefactor = getshadefactor(d, p, p->z)) <= 0)
		while (++y <= ft_min(fr->ybottom[p->x], p->yb))
			putpixel(d, p->x, y, 0);
	else if (!p->neighbor)
		while (++y <= ft_min(fr->ybottom[p->x], p->yb))
		{
			if (p->wall->posterpicnum >= 0 && y > ya_poster && y < yb_poster)
				putpixel(d, p->x, y, shade(shadefactor, ((uint32_t*)poster->pixels)[
							u_poster + (unsigned int)(norm(y, ya_poster, yb_poster) *
								poster->h) % poster->h * poster->w]));
			else
				putpixel(d, p->x, y, shade(shadefactor, ((uint32_t*)tex->pixels)[u +
							(unsigned int)(norm(y, p->yc, p->yd) * p->y_scale *
								tex->h) % tex->h * tex->w]));
		}
	else if (p->neighbor)
	{
		while (++y <= ft_min(fr->ybottom[p->x], p->nya))
			putpixel(d, p->x, y, shade(shadefactor, ((uint32_t*)tex->pixels)[u +
						(unsigned int)((p->wall->is_door ? norm(y, p->nya -
								p->doorheight, p->nya) : norm(y, p->yc, p->yd)
								* p->y_scale) * tex->h) % tex->h * tex->w]));
		tex = d->textures[p->wall->lowerpicnum];
		u = (unsigned int)(p->u * tex->w) % tex->w;
		y = ft_max(fr->ytop[p->x], p->nyb) - 1;
		while (++y <= ft_min(fr->ybottom[p->x], p->yb))
			putpixel(d, p->x, y, shade(shadefactor, ((uint32_t*)tex->pixels)[u +
						(unsigned int)(norm(y, p->yc, p->yd) * p->y_scale *
							tex->h) % tex->h * tex->w]));
	}
	if (p->sector->slope)
		p->slopetop[p->x] = p->yb;
	if (p->sector->slopeceil)
		p->slopebottom[p->x] = p->ya;
}

void	draw_wall2(t_data *d, t_projdata *p, t_frustum *fr, t_frustum *nfr)
{
	p->n = fclamp(norm(p->x, p->x1, p->x2), 0, 1);
	p->z = 1 / lerp(p->n, p->z1, p->z2);
	p->u = lerp(p->n, p->u1, p->u2) * p->z;
	if (p->z >= p->zbufferlocal[p->x])
		return ((void)(p->visible[p->x] = false));
	p->zbufferlocal[p->x] = p->z;
	if (!p->neighbor)
		d->zbuffer[p->x] = p->z;
	p->visible[p->x] = true;
	p->ya = lerp(p->n, p->y1a, p->y2a);
	p->yb = lerp(p->n, p->y1b, p->y2b);
	p->yc = lerp(p->n, p->y1c, p->y2c);
	p->yd = lerp(p->n, p->y1d, p->y2d);
	if (p->neighbor)
	{
		p->nya = ft_max(lerp(p->n, p->ny1a, p->ny2a), p->yc);
		p->nyb = ft_min(lerp(p->n, p->ny1b, p->ny2b), p->yd);
		p->doorbottom = ft_min(p->yd, p->nyb);
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
}
