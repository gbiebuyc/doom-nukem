/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ed_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikorale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 22:00:46 by mikorale          #+#    #+#             */
/*   Updated: 2019/05/14 22:00:47 by mikorale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/*
**	texture_to_scale = 0 -> noscale
**	texture_to_scale = 1 -> scaledown
**	texture_to_scale = 2 -> scaleup
*/

#define COLOR_SELECT 0x009900

static uint32_t	get_color(int x, int y, uint32_t color, t_data *d)
{
	int	menu;

	menu = d->interface.is_on_menu;
	if (menu && x >= 6 && x < 90 && color == 0xff787878 &&
		((menu == 1 && y >= 6 && y < 34) || (menu == 2 && y >= 34 && y < 62)
		|| (menu == 3 && y >= 62 && y < 90)))
		color = COLOR_SELECT;
	return (color);
}

/*
**	p[2] -> p[0] starting position | X | in the destination
**			p[1] 				   | y |
**	r = ratio
*/

void			copy_surface_to_surface(SDL_Surface *src, SDL_Surface *dest,
												int p[2], t_data *d)
{
	double		x;
	double		y;
	uint32_t	c;
	int			pos;
	t_vec2f		r;

	r.x = d->texture_to_scale / src->w;
	r.y = d->texture_to_scale / src->h;
	y = -1;
	while ((int)++y < src->h)
	{
		x = -1;
		while ((int)++x < src->w)
		{
			pos = (d->texture_to_scale != -1) ? x * r.x + y * r.y * src->w
											: x + y * src->w;
			c = get_color(x, y, ((uint32_t*)src->pixels)[pos], d);
			if (d->texture_to_scale != -1)
				pos = (int)(p[0] + x * r.x) + (int)(p[1] + y * r.y) * dest->w;
			else
				pos = p[0] + x + (p[1] + y) * dest->w;
			((uint32_t*)dest->pixels)[pos] = c;
		}
	}
}

void			save_selected_texture(t_data *d, int x, int y)
{
	t_sector	*s;

	s = &d->sectors[d->selected_sector];
	if (x >= (W - TEXTURE_TOOLBAR + 10) && x < W - PROPERTIES_LIMIT)
	{
		x = (x - (W - TEXTURE_TOOLBAR + 10)) / 64;
		y = (y - 10) / 64;
		d->selected_texture = x + y * 4;
		if (d->selected_texture < d->nb_texture)
		{
			if (d->interface.texture_case_select == 2 && d->selected_wall >= 0)
				d->walls[d->selected_wall].middlepicnum = d->selected_texture;
			else if (d->interface.texture_case_select == 1)
				s->ceilpicnum = d->selected_texture;
			else if (d->interface.texture_case_select == 0)
				s->floorpicnum = d->selected_texture;
		}
		else
			d->selected_texture = -1;
	}
	else
		d->selected_texture = -2;
}

void			remove_backgorund_image(SDL_Surface *s)
{
	int			x;
	int			y;
	uint32_t	c;

	c = ((uint32_t*)s->pixels)[0];
	y = -1;
	while (++y < s->h)
	{
		x = -1;
		while (++x < s->w)
			if (((uint32_t*)s->pixels)[x + y * s->w] == c)
				((uint32_t*)s->pixels)[x + y * s->w] = 0xFF000000;
	}
}