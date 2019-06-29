/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 00:13:32 by nallani           #+#    #+#             */
/*   Updated: 2019/06/29 11:21:20 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	set_find_alpha(double *scale_x, double *scale_y)
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

double	find_alpha(short x, short y, uint32_t which_ret)
{
	static bool		set;
	static double	scale_x[WIDTH];
	static double	scale_y[HEIGHT];

	if (!set)
	{
		set_find_alpha(&scale_x[0], &scale_y[0]);
		set = true;
	}
	if (which_ret == GREEN_BLAST)
		return ((scale_x[x] + scale_y[y]) * 0.5);
	if (scale_x[x] > scale_y[y])
		return (scale_x[x]);
	return (scale_y[y]);
}

void	color_screen(t_args_multi_colo_buf *data)
{
	int			x;
	int			y;
	uint32_t	colo;
	uint8_t		tmp;

	x = data->start_x;
	while (++x < data->max_x)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			if (data->d->color_buf.colo == GREEN_BLAST)
				tmp = (uint8_t)((1 - find_alpha(x, y,
					data->d->color_buf.colo)) * data->d->color_buf.value);
			else
				tmp = (uint8_t)((find_alpha(x, y, data->d->color_buf.colo)) *
						data->d->color_buf.value);
			colo = data->d->color_buf.colo + (tmp << 24);
			putpixel(data->d, x, y,
					alpha(getpixel3(data->d->screen, x, y), colo));
		}
	}
}

#define MAX_THREADS 8

void	color_buffer(t_data *d)
{
	pthread_t				threads[MAX_THREADS];
	t_args_multi_colo_buf	data[MAX_THREADS];
	short					i;

	if (!d->color_buf.value)
		return ;
	i = 0;
	while (i < MAX_THREADS)
	{
		data[i].d = d;
		if (i == 0)
			data[i].start_x = -1;
		else
			data[i].start_x = data[i - 1].max_x - 1;
		data[i].max_x = WIDTH / MAX_THREADS * (i + 1);
		pthread_create(&threads[i], NULL, (void *)color_screen, &data[i]);
		i++;
	}
	while (--i >= 0)
		pthread_join(threads[i], NULL);
	if (data->d->color_buf.colo == GREEN_BLAST)
		data->d->color_buf.value -= 6;
	else
		data->d->color_buf.value -= 1;
	data->d->color_buf.value = ft_max(0, data->d->color_buf.value);
}

void	change_buf_colo(t_data *d, uint16_t amount, uint32_t colo)
{
	if (d->color_buf.colo != colo)
	{
		d->color_buf.value = 0;
		d->color_buf.colo = colo;
	}
	d->color_buf.value += amount * 18;
	if (d->color_buf.value > MAX_BUF_VALUE)
		d->color_buf.value = MAX_BUF_VALUE;
}
