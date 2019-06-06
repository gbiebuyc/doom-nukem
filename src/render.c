/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 01:06:49 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/06 22:46:43 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		set_find_alpha(double *scale_x, double *scale_y)
{
	short	x;
	short	y;

	x = -1;
	while (++x < WIDTH)
		scale_x[x] = fabs(x - WIDTH * 0.5) / (WIDTH * 0.5);
	y = -1;
	while (++y < HEIGHT)
		scale_y[y] = fabs(y - HEIGHT * 0.5) / (HEIGHT * 0.5);
}

double		find_alpha(short x, short y)// a mettre en statique plutot que de calculer
{
	static bool		set;
	static double	scale_x[WIDTH];
	static double	scale_y[HEIGHT];

	if (!set)
	{
		set_find_alpha(&scale_x[0], &scale_y[0]);
		set = true;
	}
//	scale_x = fabs(x - WIDTH * 0.5);
//	scale_x = scale_x / (WIDTH * 0.5);
//	scale_y = fabs(y - HEIGHT * 0.5);
//	scale_y = scale_y / (HEIGHT * 0.5);
	return ((scale_x[x] + scale_y[y]) * 0.5);
	//if (scale_x > scale_y)
	//	return (scale_x);
	//return (scale_y);
}

uint32_t		getpixel3(SDL_Surface *s, short x, short y);

void	color_screen(t_data *d)
{
	int		x;
	int		y;
	uint32_t	colo;
	uint8_t		tmp;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			tmp = (uint8_t)(find_alpha(x, y) * d->color_buf.value);
			colo = (0xFF << d->color_buf.colo) + (tmp << 24);
			putpixel(d, x, y, alpha(getpixel3(d->screen, x, y), colo));
		}
	}
	d->color_buf.value--;
}

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
	SDL_UpdateWindowSurface(d->win);
}
