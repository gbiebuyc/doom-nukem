/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 01:06:49 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/04/29 01:33:25 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	render(t_data *d)
{
	ft_memset(d->screen->pixels, 0, d->screen->pitch * d->screen->h);
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
	SDL_UpdateWindowSurface(d->win);
}
