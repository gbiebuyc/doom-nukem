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

void	draw_sky(t_data *d, t_projdata *p, t_frustum *fr)
{
	SDL_Surface *tex;
	int			h;
	int			v;

	if (p->neighbor && p->neighbor->outdoor)
		return ;
	tex = d->textures[p->sector->ceilpicnum];
	h = HEIGHT + MAX_Y_OFFSET * 2;
	p->x = p->cx1 - 1;
	while (++p->x <= p->cx2)
	{
		p->u = (int)(((double)p->x + d->cam.rot * 1000) /
				(WIDTH * (h / HEIGHT)) * tex->w) % tex->w;
		p->y = ft_min(fr->ybottom[p->x], lerp(fclamp(norm(p->x,
							p->x1, p->x2), 0, 1), p->y1a, p->y2a)) + 1;
		while (--p->y >= fr->ytop[p->x])
		{
			v = ((double)p->y + d->cam.y_offset + MAX_Y_OFFSET) / h * tex->h;
			putpixel(d, p->x, p->y, ((uint32_t*)tex->pixels)[
					(int)p->u + v * tex->w]);
		}
	}
}

void	draw_ceil2(t_data *d, t_projdata *p, int y)
{
	if (p->floor_u1[y] == 0)
	{
		p->z = p->floor_alt[1] /
			-((p->y - HEIGHT * 0.5 + d->cam.y_offset) / (HEIGHT * 0.5));
		p->floor_u1[y] = d->cam.pos.x + p->cos * p->z - p->sin * p->z * 0.5;
		p->floor_u2[y] = d->cam.pos.x + p->cos * p->z + p->sin * p->z * 0.5;
		p->floor_v1[y] = d->cam.pos.z + p->sin * p->z + p->cos * p->z * 0.5;
		p->floor_v2[y] = d->cam.pos.z + p->sin * p->z - p->cos * p->z * 0.5;
		p->floor_shade[y] = getshadefactor(d, p);
	}
	putpixel(d, p->x, p->y, shade(p->floor_shade[y], getpixel2(
					d->textures[p->sector->ceilpicnum],
					lerp(p->xnorm, p->floor_u1[y], p->floor_u2[y]),
					lerp(p->xnorm, p->floor_v1[y], p->floor_v2[y]))));
}

void	draw_ceil(t_data *d, t_projdata *p, t_frustum *fr)
{
	if (p->floor_alt[1] <= 0)
		return ;
	p->x = p->cx1 - 1;
	while (++p->x <= p->cx2)
	{
		p->xnorm = (double)p->x / WIDTH;
		p->y = ft_min(fr->ybottom[p->x], lerp(fclamp(norm(p->x,
							p->x1, p->x2), 0, 1), p->y1a, p->y2a)) + 1;
		while (--p->y >= fr->ytop[p->x])
			draw_ceil2(d, p, p->y);
	}
}

void	*draw_ceil_thread(void *void_arg)
{
	t_thread_arg	*arg;

	arg = (t_thread_arg*)void_arg;
	if (arg->p->sector->outdoor)
		draw_sky(arg->d, arg->p, arg->fr);
	else
		draw_ceil(arg->d, arg->p, arg->fr);
	return (NULL);
}
