/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 23:47:23 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/04/30 04:00:35 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		put_pixel_to_surface(SDL_Surface *sur, int x, int y, uint32_t color)
{
	if (x >= 0 && y >= 0 && x < sur->w && y < sur->h)
		((uint32_t*)sur->pixels)[x + y * sur->w] = color;
}

void		putpixel(t_data *d, int x, int y, uint32_t color)
{
	if (x >= 0 && y >= 0 && x < W && y < H)
	{
		if (!d->interface.prompt_map_open)
			((uint32_t*)d->screen->pixels)[x + y * W] = color;
		else if (d->interface.prompt_map_open &&
				(x < MAP_PROMPT_X || x > MAP_PROMPT_ENDX ||
				y < MAP_PROMPT_Y - 25 || y > MAP_PROMPT_ENDY))
			((uint32_t*)d->screen->pixels)[x + y * W] = color;
	}
}
