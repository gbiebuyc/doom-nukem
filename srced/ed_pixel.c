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
		((uint32_t*)d->screen->pixels)[x + y * W] = color;
}

uint32_t	getpixel(SDL_Surface *s, double x, double y)
{
	int realx;
	int realy;

	realx = s->w * x;
	realy = s->h * y;
	if (realx >= 0 && realy >= 0 && realx < s->w && realy < s->h)
		return (((uint32_t*)s->pixels)[realx + realy * s->w]);
	return (0);
}

uint32_t	getpixel2(SDL_Surface *s, double x, double y)
{
	return (getpixel(s, (x >= 0 && x < 1.0) ? x : x - floor(x),
				(y >= 0 && y < 1.0) ? y : y - floor(y)));
}

uint32_t	rgb_to_pixel(SDL_Surface *surface, int r, int g, int b)
{
	return (SDL_MapRGBA(surface->format, r, g, b, 255));
}
