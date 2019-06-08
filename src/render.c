/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 01:06:49 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/08 20:54:32 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	render(t_data *d)
{
	t_frustum fr;
	fr.x1 = 0;
	fr.x2 = WIDTH - 1;
	ft_memset(fr.visitedportals, 0, sizeof(fr.visitedportals));
	for(int x = 0; x < WIDTH; ++x)
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
	draw_aim_cross(d);
	/***/

	draw_string(d, "Ceci est un test 1234567890", 50, 50, 0x0);

	SDL_UpdateWindowSurface(d->win);
}
