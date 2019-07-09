/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_end.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 02:59:09 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/07/09 23:24:10 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		rainbow_font(int y)
{
	double	r;
	int		colo;

	r = M_PI / 2 * HEIGHT;
	colo = (int)(sin(y + r) * 127 + 128);
	colo += (int)(sin(y + 2 + r) * 127 + 128) << 8;
	colo += (int)(sin(y + 4 + r) * 127 + 128) << 16;
	return (colo);
}

void	the_end(t_data *d)
{
	int y;
	int	colo;

	y = HEIGHT - 100;
	play_music(d, PIKA_SONG);
	while (y > -1 * HEIGHT)
	{
		colo = rainbow_font(y);
		ft_memset(d->screen->pixels, 0, d->screen->pitch * d->screen->h);
		draw_string(d, (t_font){"Felicitations, \nyou saved \nPikachu !!\n\
				Good luck \non your way\nto be the\nvery best"
				, WIDTH / 50, y, colo, 6});
		SDL_UpdateWindowSurface(d->win);
		SDL_Delay(10);
		y -= 1;
	}
	proper_exit(d);
}
