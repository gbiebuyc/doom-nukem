/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 17:04:34 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/30 14:13:33 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	draw_wall_transparent2(t_data *d, t_projdata *p, t_frustum *fr)
{
	int			y;
	uint32_t	px;

	p->tex = d->textures[p->wall->middlepicnum];
	p->u_tex = (p->u - floor(p->u)) * p->tex->w;
	y = fr->ytop[p->x];
	p->shadefactor = getshadefactor(d, p, p->z);
	while (++y <= fr->ybottom[p->x])
	{
		px = getpixel4(p->tex, p->u_tex,
				norm(y, p->yc, p->yd) * p->y_scale);
		if ((px >> 24) == 0xff)
			putpixel2(d, p->z, (t_vec2){p->x, y},
					shade(p->shadefactor, px));
	}
}

void	draw_wall_transparent(t_data *d, t_projdata *p, t_frustum *fr)
{
	p->n = fclamp(norm(p->x, p->x1, p->x2), 0, 1);
	p->z = 1 / lerp(p->n, p->z1, p->z2);
	p->u = lerp(p->n, p->u1, p->u2) * p->z;
	p->ya = lerp(p->n, p->y1a, p->y2a);
	p->yb = lerp(p->n, p->y1b, p->y2b);
	p->yc = lerp(p->n, p->y1c, p->y2c);
	p->yd = lerp(p->n, p->y1d, p->y2d);
	if (p->neighbor)
	{
		p->nya = lerp(p->n, p->ny1a, p->ny2a);
		p->nyb = lerp(p->n, p->ny1b, p->ny2b);
		p->doorbottom = ft_min(p->yd, p->nyb);
		p->doorheight = p->doorbottom - p->yc;
		p->nya += (p->doorbottom - ft_max(p->yc, p->nya)) *
			(1 - d->doorstate[p->wall - d->walls]);
	}
	draw_wall_transparent2(d, p, fr);
}

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

void	draw_wall_no_nei(t_data *d, t_projdata *p, t_frustum *fr)
{
	uint32_t px;

	while (++p->y <= ft_min(fr->ybottom[p->x], p->yb))
		if (p->wall->posterpicnum >= 0 &&
			p->y > p->ya_poster && p->y < p->yb_poster && (((px =
			getpixel4(p->poster, p->u_poster, norm(p->y, p->ya_poster,
			p->yb_poster))) >> 24) > 128))
			putpixel2(d, p->z, (t_vec2){p->x, p->y}, shade(p->shadefactor, px));
		else
			putpixel2(d, p->z, (t_vec2){p->x, p->y}, shade(p->shadefactor,
						getpixel4(p->tex, p->u_tex,
							norm(p->y, p->yc, p->yd) * p->y_scale)));
}
