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

#define COLOR_SELECT 0x009900

static uint32_t	get_color(int x, int y, uint32_t color, t_data *d)
{
	int	menu;

	menu = d->interface.is_on_menu;
	if (menu && x >= 5 && x <= 90 && color == 0xff787878 &&
		((menu == 1 && y >= 5 && y < 34) || (menu == 2 && y >= 34 && y < 62)
		|| (menu == 3 && y >= 62 && y <= 90)))
		color = COLOR_SELECT;
	return (color);
}

/*
**	p[2] -> p[0] starting position | X | in the destination
**			p[1] 				   | y |
*/

void			copy_surface_to_surface(SDL_Surface *src, SDL_Surface *dst,
												int p[2], t_data *d)
{
	int			x;
	int			y;

	y = -1;
	while (++y < src->h && (x = -1))
		while (++x < src->w)
			if (p[0] + x >= 0 && p[0] + x < W && p[1] + y >= 0 && p[1] + y < H)
				((uint32_t*)dst->pixels)[p[0] + x + (p[1] + y) * dst->w] =
				get_color(x, y, ((uint32_t*)src->pixels)[x + y * src->w], d);
}

void			cpy_scale_surf(SDL_Surface *src, int p[2], int size, t_data *d)
{
	int			x;
	int			y;
	uint32_t	c;

	y = -1;
	while (++y < size && size > 0 && (x = -1))
		while (++x < size)
			if (p[0] + x >= 0 && p[0] + x < W && p[1] + y >= 0 && p[1] + y < H)
				if (!d->interface.prompt_map_open ||
					(d->interface.prompt_map_open &&
					(x + p[0] < MAP_PROMPT_X || x + p[0] > MAP_PROMPT_ENDX ||
					y + p[1] < MAP_PROMPT_Y - 25 ||
					y + p[1] > MAP_PROMPT_ENDY)))
				{
					c = ((uint32_t*)src->pixels)[
					(int)((double)x / size * src->w) +
					(int)((double)y / size * src->h) * src->w];
					if (c >> 24 == 255)
						((uint32_t*)d->screen->pixels)[(x + p[0]) +
						(y + p[1]) * d->screen->w] = c;
				}
}

double			fclamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}
