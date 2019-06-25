/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_aim_cross.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 19:18:06 by nallani           #+#    #+#             */
/*   Updated: 2019/06/25 22:37:06 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	draw_blaster_aim(t_data *d)
{
	short i;

	i = (WIDTH * 0.5) - 10;
	while (--i > (WIDTH >> 1) - 22)
		putpixel(d, i, HEIGHT >> 1, GREEN_BLAST);
	i = (WIDTH * 0.5) + 10;
	while (++i < (WIDTH >> 1) + 22)
		putpixel(d, i, HEIGHT >> 1, GREEN_BLAST);
	putpixel(d, (WIDTH >> 1) + 1, HEIGHT >> 1, GREEN_BLAST);
	putpixel(d, (WIDTH >> 1) - 1, HEIGHT >> 1, GREEN_BLAST);
	putpixel(d, WIDTH >> 1, HEIGHT >> 1, GREEN_BLAST);
}

void	draw_aim_cross(t_data *d)
{
	short		i;
	uint32_t	colo;

	if (d->player.current_weapon == M16)
		colo = 0xFF0000;
	if (d->player.current_weapon == BLASTER)
	{
		draw_blaster_aim(d);
		return ;
	}
	if (d->player.current_weapon == CRYO_BALLISTA)
		colo = 0xDDFF;
	i = -1;
	while (++i < 10)
		putpixel(d, (WIDTH >> 1) - 16 + i, HEIGHT >> 1, colo);
	i += 12;
	while (++i < 32)
		putpixel(d, (WIDTH >> 1) - 16 + i, HEIGHT >> 1, colo);
	i = -1;
	while (++i < 10)
		putpixel(d, WIDTH >> 1, (HEIGHT >> 1) - 16 + i, colo);
	i += 12;
	while (++i < 32)
		putpixel(d, WIDTH >> 1, (HEIGHT >> 1) - 16 + i, colo);
	putpixel(d, WIDTH >> 1, HEIGHT >> 1, colo);
}
