/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:38:27 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/05/07 03:54:26 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	draw_wall(t_data *d, t_projdata *p, t_frustum *fr)
{
	t_frustum	nfr;
	int			nya;
	int			nyb;
	bool		visible[WIDTH];

	nya = 0;
	nyb = 0;
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
	for (int x = p->cx1; x <= p->cx2; x++)
	{
		double n = norm(x, p->x1, p->x2);
		n = fclamp(n, 0, 1);
		double z = 1 / lerp(n, p->z1, p->z2);
		double u = lerp(n, p->u_begin, p->u_end) * z;

		if (z >= p->zbuffer[x])
		{
			visible[x] = false;
			continue ;
		}
		p->zbuffer[x] = z;
		visible[x] = true;

		int ya = lerp(n, p->y1a, p->y2a);
		int yb = lerp(n, p->y1b, p->y2b);
		if (p->neighbor)
		{
			nya = ft_max(lerp(n, p->ny1a, p->ny2a), ya);
			nyb = ft_min(lerp(n, p->ny1b, p->ny2b), yb);
			nfr.ytop[x] = clamp(nya, fr->ytop[x], fr->ybottom[x]);
			nfr.ybottom[x] = clamp(nyb, fr->ytop[x], fr->ybottom[x]);
		}
		for (int y = ft_max(fr->ytop[x], ya);
				y <= ft_min(fr->ybottom[x], yb); y++)
		{
			double v = lerp(norm(y, ya, yb), 0, p->y_scale);
			if (p->neighbor && y < nya)
				putpixel(d, x, y, shade(z, getpixel2(
							d->textures[p->wall->lowerpicnum], u, v)));
			else if (p->neighbor && y > nyb)
				putpixel(d, x, y, shade(z, getpixel2(
							d->textures[p->wall->lowerpicnum], u, v)));
			else if (!p->neighbor)
				putpixel(d, x, y, shade(z, getpixel2(
							d->textures[p->wall->middlepicnum], u, v)));
		}
	}
	clamp_wall(visible, &p->cx1, &p->cx2);
	if (p->neighbor && p->cx1 < p->cx2)
	{
		nfr.x1 = p->cx1;
		nfr.x2 = p->cx2;
		// recursive call
		render_sector(d, p->neighbor, &nfr);
	}
}

void	clamp_wall(bool visible[], int *x1, int *x2)
{
	int	end;

	if (*x2 - *x1 <= 2)
		return ;
	end = *x2;
	while (!visible[*x1] && *x1 < end)
		(*x1)++;
	(*x2)--;
	if (*x1 >= end)
		return ;
	*x2 = *x1;
	while (visible[*x2] && *x2 < end)
		(*x2)++;
}
