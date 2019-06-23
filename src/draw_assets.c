/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 22:49:10 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/22 22:49:10 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define ASSET_W 0.5

void	proj_asset(t_data *d, t_projdata *p, t_vec3f v, SDL_Surface *tex)
{
	double	scale;
	int		w;
	int		h;

	v.x -= d->cam.pos.x;
	v.z -= d->cam.pos.z;
	v = (t_vec3f){v.x * d->cam.cos - v.z * d->cam.sin, v.y,
		v.x * d->cam.sin + v.z * d->cam.cos};
	scale = (1.0 / v.z) * WIDTH;
	v.x = v.x * scale + WIDTH / 2;
	v.y = v.y * -scale + HEIGHT / 2 - d->cam.y_offset;
	w = scale * ASSET_W;
	h = w * tex->h / (double)tex->w;
	p->x1 = v.x - w / 2;
	p->x2 = p->x1 + w;
	p->ya = (p->is_on_floor) ? v.y - h : v.y;
	p->yb = (p->is_on_floor) ? v.y : v.y + h;
	p->z = v.z;
}

void	blit_asset(t_data *d, t_projdata *p, t_frustum *fr, SDL_Surface *tex)
{
	int			x;
	int			y;
	int			u;
	double		shadefactor;
	uint32_t	px;

	if ((shadefactor = getshadefactor(d, p, p->z)) <= 0)
		return ;
	x = p->cx1 - 1;
	while (++x <= p->cx2)
	{
		if (p->z >= p->zbuffer[x])
			continue ;
		u = norm(x, p->x1, p->x2) * tex->w;
		y = ft_max(p->ya, fr->ytop[x]);
		while (++y <= ft_min(p->yb, fr->ybottom[x]))
		{
			if (p->z >= d->zbuffer_sprites[x + y * WIDTH])
				continue ;
			d->zbuffer_sprites[x + y * WIDTH] = p->z;
			px = getpixel4(tex, u, norm(y, p->ya, p->yb));
			if ((px >> 24) > 127)
				putpixel(d, x, y, shade(shadefactor, px));
		}
	}
}

void	draw_assets(t_data *d, t_projdata *p, t_frustum *fr, int16_t sectnum)
{
	int			i;
	t_assets	*asset;

	sectnum = p->sector - d->sectors;
	i = -1;
	while (d->nb_assets && ++i < d->assets[sectnum][0].nb_assets)
	{
		asset = &d->assets[sectnum][i];
		if (asset->used)
			continue ;
		t_vec3f v = vec2to3(asset->world_pos);
		v.y = (asset->is_on_floor) ? get_floordh(d, p->sector, v) :
			get_ceildh(d, p->sector, v);
		p->is_on_floor = asset->is_on_floor;
		proj_asset(d, p, v, d->assets_texture[asset->picnum]);
		p->cx1 = ft_max(p->x1, fr->x1);
		p->cx2 = ft_min(p->x2, fr->x2);
		blit_asset(d, p, fr, d->assets_texture[asset->picnum]);
	}
}
