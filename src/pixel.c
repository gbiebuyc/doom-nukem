/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 23:47:23 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/05/12 18:11:08 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	putpixel(t_data *d, int x, int y, uint32_t color)
{
	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
		((uint32_t*)d->screen->pixels)[(int)x + (int)y * WIDTH] = color;
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
	unsigned int realx;
	unsigned int realy;

	realx = (unsigned int)(s->w * x) % s->w;
	realy = (unsigned int)(s->h * y) % s->h;
	return (((uint32_t*)s->pixels)[realx + realy * s->w]);
}

uint32_t	rgb_to_pixel(SDL_Surface *surface, int r, int g, int b)
{
	return (SDL_MapRGBA(surface->format, r, g, b, 255));
}
