/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_end.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 02:59:09 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/19 03:10:18 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	the_end(t_data *d)
{
	int y;

	y = 0;
	while (y < HEIGHT)
	{
		ft_memset(d->screen->pixels, 0, d->screen->pitch * d->screen->h);
		draw_string(d, (t_font){"The End", WIDTH / 2 - 120, y, 0xffffff, 6});
		SDL_UpdateWindowSurface(d->win);
		SDL_Delay(10);
		y += 4;
	}
	exit(0);
}
