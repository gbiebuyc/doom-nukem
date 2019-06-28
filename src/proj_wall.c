/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proj_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 00:56:47 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/06/27 00:56:47 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	proj_wall2(t_data *d, t_projdata *p, t_frustum *fr)
{
	pthread_t		thread;
	t_thread_arg	t;

	if (p->wall->posterpicnum >= 0)
	{
		p->u1_poster = (p->len - POSTER_W) / 2.0;
		p->u2_poster = p->len - p->u1_poster;
		p->poster_h = POSTER_W * ((double)d->posters[p->wall->posterpicnum]->h /
				d->posters[p->wall->posterpicnum]->w) / p->y_scale;
	}
	draw_wall(d, p, fr);
	t = (t_thread_arg){d, p, fr};
	if (pthread_create(&thread, NULL, draw_ceil_thread, &t))
		exit(ft_printf("pthread_create error\n"));
	draw_floor(d, p, fr);
	if (pthread_join(thread, NULL))
		exit(ft_printf("pthread_join error\n"));
}

void	proj_wall(t_data *d, t_projdata *p, t_frustum *fr, t_vec2f v[2])
{
	double y_offset;

	p->scale1 = (1.0 / p->z1) * WIDTH;
	p->scale2 = (1.0 / p->z2) * WIDTH;
	p->x1 = p->x1 * p->scale1 + WIDTH / 2;
	p->x2 = p->x2 * p->scale2 + WIDTH / 2;
	y_offset = HEIGHT / 2 - d->cam.y_offset;
	p->y1a = get_ceildh(d, p->sector, v[0]) * -p->scale1 + y_offset;
	p->y2a = get_ceildh(d, p->sector, v[1]) * -p->scale2 + y_offset;
	p->y1b = get_floordh(d, p->sector, v[0]) * -p->scale1 + y_offset;
	p->y2b = get_floordh(d, p->sector, v[1]) * -p->scale2 + y_offset;
	p->y1c = (p->sector->ceilheight - d->cam.pos.y) * -p->scale1 + y_offset;
	p->y2c = (p->sector->ceilheight - d->cam.pos.y) * -p->scale2 + y_offset;
	p->y1d = (p->sector->floorheight - d->cam.pos.y) * -p->scale1 + y_offset;
	p->y2d = (p->sector->floorheight - d->cam.pos.y) * -p->scale2 + y_offset;
	p->y_scale = p->sector->ceilheight - p->sector->floorheight;
	if (p->neighbor)
	{
		p->ny1a = get_ceildh(d, p->neighbor, v[0]) * -p->scale1 + y_offset;
		p->ny2a = get_ceildh(d, p->neighbor, v[1]) * -p->scale2 + y_offset;
		p->ny1b = get_floordh(d, p->neighbor, v[0]) * -p->scale1 + y_offset;
		p->ny2b = get_floordh(d, p->neighbor, v[1]) * -p->scale2 + y_offset;
	}
	proj_wall2(d, p, fr);
}
