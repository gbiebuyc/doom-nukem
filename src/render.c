/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 01:06:49 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/07 00:36:59 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	render(t_data *d)
{
	t_frustum fr;
	fr.x1 = 0;
	fr.x2 = WIDTH - 1;
	ft_memset(fr.visitedportals, 0, sizeof(fr.visitedportals));
	for(int x = 0; x < WIDTH; ++x) // to change with HUD ?
	{
		fr.ytop[x] = 0;
		fr.ybottom[x] = HEIGHT-1;
	}
	render_sector(d, &d->sectors[d->cursectnum], &fr);
	draw_weapon(d);
	if (d->color_buf.value)
		color_screen(d);
	//draw_hud(d);
	/***/
	int i = -1;

	while (++i < 32)
		putpixel(d, (WIDTH >> 1) - 16 + i, HEIGHT >> 1, 0x22FF00);
	i = -1;
	while (++i < 32)
		putpixel(d, WIDTH >> 1, (HEIGHT >> 1) - 16 + i, 0x22FF00);
	/***/
	SDL_UpdateWindowSurface(d->win);
}
