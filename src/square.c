/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 16:57:58 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/04/05 18:34:10 by gbiebuyc         ###   ########.fr       */
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
		//t_vec2f test;
		//test = projection(cube[i], d->camera.dir, d->camera.pos);
		//putpixel(d, test.x, test.y, 0xffffff);
		t_vec3f new;
		new = get_projected_vertex(d, cube[i]);
		putpixel(d, new.x, new.y, 0xffffff);
		i++;
	}
	/*
	t_texture3d ret;
	i = 0;
	while (i < 4)
	{
		ret.vertex[i] = cube[i];
		i++;
	}
	draw_texture(d, ret, *d->texture[0]);
//	printf("R%d\n", d->main_win.surface->format->Rmask);
//	printf("G%d\n", d->main_win.surface->format->Gmask);
//	printf("B%d\n", d->main_win.surface->format->Bmask);
//	printf("A%d\n", d->main_win.surface->format->Amask);
//	printf("win: %d\n", d->main_win.surface->format->format);
//	printf("rgba32: %d\n", SDL_PIXELFORMAT_RGBA32);
//	printf("argb32: %d\n", SDL_PIXELFORMAT_ARGB32);
//	printf("bgra32: %d\n", SDL_PIXELFORMAT_BGRA32);
//	printf("text: %d\n", d->texture[0]->format->format);
//	printf("ABGR32: %d\n", SDL_PIXELFORMAT_ABGR32);
	*/
}
