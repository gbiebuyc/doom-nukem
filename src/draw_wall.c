/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:38:27 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/04/08 19:54:34 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

double edge_function(t_vec3f a, t_vec3f b, t_vec3f c)
{
	return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}

void	raster_triangle(t_data *d, t_vec3f v[3])
{
	// couleurs des vertex
	int c0[3] = {255, 0, 0};
	int c1[3] = {0, 255, 0};
	int c2[3] = {0, 0, 255};
	double area = edge_function(v[0], v[1], v[2]);
	for (int y = 0; y < WIN_LENGTH; y++)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			t_vec3f p = {x, y, 0};
			double w0 = edge_function(v[1], v[2], p);
			double w1 = edge_function(v[2], v[0], p);
			double w2 = edge_function(v[0], v[1], p);
			if (w0 >= 0 && w1 >= 0 && w2 >= 0)
			{
				w0 /= area;
				w1 /= area;
				w2 /= area;
				int r = w0 * c0[0] + w1 * c1[0] + w2 * c2[0];
				int g = w0 * c0[1] + w1 * c1[1] + w2 * c2[1];
				int b = w0 * c0[2] + w1 * c1[2] + w2 * c2[2];
				putpixel(d, x, y, rgb_to_pixel(d->main_win.surface,
							r, g, b));
			}
		}
	}
}

void	draw_wall(t_data *d, t_wall wall)
{
	SDL_Surface *tex = d->texture[0];
	(void)tex;
	raster_triangle(d,
			(t_vec3f[3]){wall.a, wall.c, wall.b});
	raster_triangle(d,
			(t_vec3f[3]){wall.a, wall.d, wall.c});
}
