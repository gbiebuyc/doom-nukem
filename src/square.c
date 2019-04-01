/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 16:57:58 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/04/01 18:28:16 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	square(t_data *d)
{
	t_vec3f cube[8];
	t_vec3f projected;

	cube[0] = (t_vec3f){-1, 1, -1};
	cube[1] = (t_vec3f){1, 1, -1};
	cube[2] = (t_vec3f){1, -1, -1};
	cube[3] = (t_vec3f){-1, -1, -1};
	cube[4] = (t_vec3f){-1, 1, 1};
	cube[5] = (t_vec3f){1, 1, 1};
	cube[6] = (t_vec3f){1, -1, 1};
	cube[7] = (t_vec3f){-1, -1, 1};

	int i = 0;
	ft_memset(d->main_win.surface->pixels, 0, d->main_win.surface->w * d->main_win.surface->h * 4);
	while (i < 8)
	{
		projected = sub_vec3f(cube[i], d->camera.pos);
		projected.x /= projected.z;
		projected.y /= projected.z;
		projected.x = projected.x  * WIN_WIDTH + WIN_WIDTH / 2;
		projected.y = projected.y * -WIN_WIDTH + WIN_LENGTH / 2;
		printf("i:%d  x:%f  y%f z:%f camx:%f\n", i, projected.x, projected.y, projected.z, d->camera.pos.x);

		((uint32_t*)d->main_win.surface->pixels)[(int)projected.x + (int)projected.y * WIN_WIDTH] =
			(uint32_t)0xffffff;
		i++;
	}
}
