/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 16:57:58 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/04/02 15:21:02 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	putpixel(t_data *d, int x, int y, uint32_t color)
{
	if (x >= 0 && y >= 0 && x < WIN_WIDTH && y < WIN_LENGTH)
		((uint32_t*)d->main_win.surface->pixels)[(int)x + (int)y * WIN_WIDTH] = color;
}

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
	ft_memset(d->main_win.surface->pixels, 0,
			d->main_win.surface->w * d->main_win.surface->h * 4);
	while (i < 8)
	{
		projected = sub_vec3f(cube[i], d->camera.pos);
		// Y Rotation
		double xtmp = projected.x;
		double ztmp = projected.z;
		double angle = get_vec2f_angle(
				(t_vec2f){d->camera.dir.x, d->camera.dir.z}, (t_vec2f){0, 1});
		projected.x = cos(angle) * xtmp - sin(angle) * ztmp;
		projected.z = sin(angle) * xtmp + cos(angle) * ztmp;
		projected.x /= projected.z;
		projected.y /= projected.z;
		projected.x = projected.x  * WIN_WIDTH + WIN_WIDTH / 2;
		projected.y = projected.y * -WIN_WIDTH + WIN_LENGTH / 2;
		putpixel(d, projected.x, projected.y, 0xffffff);
		i++;
	}
}
