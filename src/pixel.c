/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 23:47:23 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/07 20:09:32 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

/*
** add this file as library with extern inline keyword
*/
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

uint32_t		getpixel3(SDL_Surface *s, short x, short y)
{
	return (((uint32_t*)s->pixels)[x + y * s->w]);
}

uint32_t	alpha(uint32_t	old_colo, uint32_t	new_colo)
{
	double			percent;
	double			rev_percent;
	uint8_t			R[2];
	uint8_t			G[2];
	uint8_t			B[2];
	//uint8_t			A[2];

//	if(new_colo != 0x1F170B)// trash fix for windows
//return (new_colo);
	if (!(new_colo >> 24))
		return (old_colo);
	if (new_colo >> 24 == 0xFF)
		return (new_colo);
	percent = ((new_colo >> 24) & 0xFF) / 255.0;// >> 24 for mac
	rev_percent = 1 - percent;

	R[0] = (uint8_t)(old_colo >> 16 & 0xFF) * rev_percent;
	G[0] = (uint8_t)(old_colo >> 8 & 0xFF) * rev_percent;
	B[0] = (uint8_t)(old_colo & 0xFF) * rev_percent;
//	A[0] = (uint8_t)(old_colo >> 24 & 0xFF) * rev_percent; // alpha a revoir ( useless ?)

	R[1] = (uint8_t)(new_colo >> 16 & 0xFF) * percent;
	G[1] = (uint8_t)(new_colo >> 8 & 0xFF) * percent;
	B[1] = (uint8_t)(new_colo & 0xFF) * percent;
//	A[1] = (uint8_t)(new_colo  >> 24 & 0xFF); // alpha  revoir (useless ?)

	return (((R[0] + R[1]) << 16) + ((G[0] + G[1]) << 8) + (B[0] + B[1]));// + ((A[0] + A[1]) << 24));
}
