/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 23:47:23 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/28 15:27:17 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		putpixel(t_data *d, int x, int y, uint32_t color)
{
	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
		((uint32_t*)d->screen->pixels)[x + y * WIDTH] = color;
}

void		putpixel2(t_data *d, double z, t_vec2 p, uint32_t color)
{
	p.x = p.x + p.y * WIDTH;
	if (!(p.x >= 0 && p.x < WIDTH * HEIGHT))
		return ;
	((uint32_t*)d->screen->pixels)[p.x] = color;
	d->zbuffer[p.x] = z;
}

uint32_t	alpha(uint32_t old_colo, uint32_t new_colo)
{
	double			percent;
	double			rev_percent;
	uint8_t			r[2];
	uint8_t			g[2];
	uint8_t			b[2];

	if (!(new_colo >> 24))
		return (old_colo);
	if (new_colo >> 24 == 0xFF)
		return (new_colo);
	percent = ((new_colo >> 24) & 0xFF) / 255.0;
	rev_percent = 1 - percent;
	r[0] = (uint8_t)(old_colo >> 16 & 0xFF) * rev_percent;
	g[0] = (uint8_t)(old_colo >> 8 & 0xFF) * rev_percent;
	b[0] = (uint8_t)(old_colo & 0xFF) * rev_percent;
	r[1] = (uint8_t)(new_colo >> 16 & 0xFF) * percent;
	g[1] = (uint8_t)(new_colo >> 8 & 0xFF) * percent;
	b[1] = (uint8_t)(new_colo & 0xFF) * percent;
	return (((r[0] + r[1]) << 16) + ((g[0] + g[1]) << 8) + (b[0] + b[1]));
}
