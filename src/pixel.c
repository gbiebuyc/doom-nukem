/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 23:47:23 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/04/07 23:48:34 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	putpixel(t_data *d, int x, int y, uint32_t color)
{
	if (x >= 0 && y >= 0 && x < WIN_WIDTH && y < WIN_LENGTH)
		((uint32_t*)d->main_win.surface->pixels)[(int)x + (int)y * WIN_WIDTH] = color;
}

uint32_t	getpixel(SDL_Surface *s, int x, int y)
{
	if (x >= 0 && y >= 0 && x < s->w && y < s->h)
		return (((uint32_t*)s->pixels)[(int)x + (int)y * s->w]);
	return (0);
}

// looping on the texture
uint32_t	getpixel2(SDL_Surface *s, int x, int y)
{
	return (((uint32_t*)s->pixels)[(int)x % s->w  + (int)y % s->h * s->w]);
}
