/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 00:13:32 by nallani           #+#    #+#             */
/*   Updated: 2019/06/07 00:19:16 by nallani          ###   ########.fr       */
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
	if (d->color_buf.value < 3)
		d->color_buf.value = 0;
	else
	d->color_buf.value -= 2;
}
void	change_buf_colo(t_data *d, uint16_t amount, uint8_t colo)
{
	if (d->color_buf.colo != colo)
	{
		d->color_buf.value = 0;
		d->color_buf.colo = colo;
	}
	d->color_buf.value += (amount * 25); // a revoir en fonction de vie max
	if (d->color_buf.value > MAX_BUF_VALUE)
		d->color_buf.value = MAX_BUF_VALUE;
}
