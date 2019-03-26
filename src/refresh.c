/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 22:40:33 by nallani           #+#    #+#             */
/*   Updated: 2019/03/26 03:37:39 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define NB_OF_THREADS 4

void		set_args(t_args *args, t_data *d, t_vec2f ray_dir, short x)
{
	args->d = d;
	args->ray_dir = ray_dir;
	args->x = x;
	args->angle = get_vec2f_angle(d->player.dir, ray_dir);
}

// a effacer, fonction dans intersection.c (unfinished)
void		find_intersection(t_args * args)
{
	(void)args;
}

void		main_raycast_multithread(t_data *d, int x, int tmp)
{
	t_vec2f		ray_dir;
	pthread_t	id[NB_OF_THREADS];
	t_args		args[NB_OF_THREADS];

	x = 0;
	while(x < WIN_WIDTH)
	{
		tmp = 0;
		while (tmp < NB_OF_THREADS)
		{
			ray_dir = add_vec2f(d->player.dir, mul_vec2f(d->player.plane, 2.0 *
						(x + tmp) / WIN_WIDTH - 1.0));
			set_args(&args[tmp], d, ray_dir, WIN_WIDTH - x - tmp);
			if (pthread_create(&id[tmp], NULL, (void *)&find_intersection
						, &args[tmp]))
				err_exit(d, 100/*a changer*/, strerror(errno));
			tmp++;
		}
		x += NB_OF_THREADS;
	}
}

void		refresh_img(t_data *d)
{	
	main_raycast_multithread(d, 0, 0);
	SDL_UpdateWindowSurface(d->main_win.win);
}
