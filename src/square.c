/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 16:57:58 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/04/02 21:07:19 by nallani          ###   ########.fr       */
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
		t_vec2f test;
		test = projection(cube[i], d->camera.dir, d->camera.pos);
		putpixel(d, test.x, test.y, 0xffffff);
		i++;
	}
	t_texture3d ret;
	i = 0;
	while (i < 4)
	{
		ret.vertex[i] = cube[i];
		i++;
	}
	draw_texture(d, ret, *d->texture[0]);
}