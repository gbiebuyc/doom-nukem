/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 00:21:32 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/26 00:24:13 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

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

	realx = s->w * (x - floor(x));
	realy = s->h * (y - floor(y));
	return (((uint32_t*)s->pixels)[realx + realy * s->w]);
}

uint32_t	getpixel3(SDL_Surface *s, short x, short y)
{
	return (((uint32_t*)s->pixels)[x + y * s->w]);
}

uint32_t	getpixel4(SDL_Surface *s, int u, double y)
{
	return (((uint32_t*)s->pixels)[u +
			(int)(s->h * (y - floor(y))) * s->w]);
}
