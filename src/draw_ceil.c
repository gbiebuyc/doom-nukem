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
	int			x;
	int			y;

	if (p->neighbor && p->neighbor->outdoor)
		return ;
	tex = d->textures[p->sector->ceilpicnum];
	h = HEIGHT + MAX_Y_OFFSET * 2;
	x = p->cx1 - 1;
	while (++x <= p->cx2)
	{
		p->u = (unsigned int)(((double)x + d->cam.rot * 1000) /
				(WIDTH * (h / HEIGHT)) * tex->w) % tex->w;
		y = ft_min(fr->ybottom[x], lerp(fclamp(norm(x,
							p->x1, p->x2), 0, 1), p->y1a, p->y2a)) + 1;
		while (--y >= fr->ytop[x])
		{
			v = ((double)y + d->cam.y_offset + MAX_Y_OFFSET) / h * tex->h;
			putpixel(d, x, y, ((uint32_t*)tex->pixels)[
					(int)p->u + v * tex->w]);
		}
	}
}

void	proj_ceil(t_data *d, t_projdata *p)
{
	double y_offset;

	p->b[0] = transform_back(d, (t_vec3f){-1, 0, 1});
	p->b[1] = transform_back(d, (t_vec3f){1, 0, 1});
	p->b[2] = transform_back(d, (t_vec3f){0, 0, 2});
	y_offset = HEIGHT / 2 - d->cam.y_offset;
	p->a[0] = (t_vec3f){-WIDTH + WIDTH / 2, get_ceildh(d,
			p->sector, vec3to2(p->b[0])) * -WIDTH + y_offset, 1};
	p->a[1] = (t_vec3f){WIDTH + WIDTH / 2, get_ceildh(d,
			p->sector, vec3to2(p->b[1])) * -WIDTH + y_offset, 1};
	p->a[2] = (t_vec3f){WIDTH / 2, get_ceildh(d, p->sector,
			vec3to2(p->b[2])) * -WIDTH * 0.5 + y_offset, 0.5};
	p->b[2].x /= 2;
	p->b[2].z /= 2;
	p->areaa = edge_function(p->a[0], p->a[1], p->a[2].x, p->a[2].y);
}

void	draw_ceil(t_data *d, t_projdata *p, t_frustum *fr)
{
	int		x;
	int		y;
	double	w[3];
	double	z;

	x = p->cx1 - 1;
	while (++x <= p->cx2)
	{
		y = ft_min(fr->ybottom[x], lerp(fclamp(norm(x,
							p->x1, p->x2), 0, 1), p->y1a, p->y2a)) + 1;
		while (--y >= fr->ytop[x])
		{
			w[0] = edge_function(p->a[1], p->a[2], x, y) / p->areaa;
			w[1] = edge_function(p->a[2], p->a[0], x, y) / p->areaa;
			w[2] = edge_function(p->a[0], p->a[1], x, y) / p->areaa;
			z = 1 / (w[0] * p->a[0].z + w[1] * p->a[1].z + w[2] * p->a[2].z);
			if (z >= d->zbuffer[x + y * WIDTH])
				continue ;
			putpixel2(d, z, (t_vec2){x, y}, shade(getshadefactor(d, p, z),
				getpixel2(d->textures[p->sector->ceilpicnum],
				(w[0] * p->b[0].x + w[1] * p->b[1].x + w[2] * p->b[2].x) * z,
				(w[0] * p->b[0].z + w[1] * p->b[1].z + w[2] * p->b[2].z) * z)));
		}
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
