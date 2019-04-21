/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:38:27 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/04/21 05:23:31 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	draw_wall(t_data *d, t_wall_clipped wall)
{
	// divide vertex-attribute by the vertex z-coordinate
	wall.left_u /= wall.left.z;
	wall.right_u /= wall.right.z;
	// pre-compute 1 over z
	wall.left.z = 1 / wall.left.z;
	wall.right.z = 1 / wall.right.z;
	for (int x = ft_max(0, wall.left.x);
			x <= ft_min(WIDTH, wall.right.x);
			x++)
	{
		// perspective correct interpolation of u texture coordinate
		double w = (x - wall.left.x) / (wall.right.x - wall.left.x);
		double u = wall.left_u * (1 - w) + wall.right_u * w;
		double z = 1 / (wall.left.z * (1 - w) + wall.right.z * w);
		u *= z;

		double y_start = wall.left.y * (1 - w) + wall.right.y * w;
		double y_end = wall.left2.y * (1 - w) + wall.right2.y * w;
		double v = 0;
		double dv = 1.0 / (y_end - y_start);
		for (int y = y_start; y <= y_end; y++)
		{
			putpixel(d, x, y, getpixel2(d->texture[wall.middlepicnum], u, v));
			v += dv;
		}
	}
}

void	draw_floor(t_data *d, t_wall_clipped wall)
{
	double w;

	int y_start = ft_min(wall.left2.y, wall.right2.y);
	int slope_end = ft_max(wall.left2.y, wall.right2.y);
	int x1 = (wall.left2.y < wall.right2.y) ? wall.left2.x : wall.right2.x;
	double altitude = d->cam.pos.y - wall.sector.floorheight;
	if (altitude <= 0)
		return ;
	altitude *= 2.7;
	double angle = -d->cam.rot.y + M_PI_2;
	for (int y = y_start; y < HEIGHT; y++)
	{
		w = (double)(y - HEIGHT / 2) / (HEIGHT / 2);
		double distance = altitude / w;
		double line_du = sin(angle) * distance;
		double line_dv = -cos(angle) * distance;
		double left_u = d->cam.pos.x + distance * cos(angle) - line_du / 2;
		double right_u = left_u + line_du;
		double left_v = d->cam.pos.z + distance * sin(angle) - line_dv / 2;
		double right_v = left_v + line_dv;

		w = fmax(0, fmin(1, (double)(y - y_start) / (slope_end - y_start)));
		int x_start = x1 * (1 - w) + wall.left2.x * w;
		int x_end = x1 * (1 - w) + wall.right2.x * w;
		for (int x = ft_max(0, x_start); x <= ft_min(WIDTH, x_end); x++)
		{
			w = (double)x / WIDTH;
			double u = left_u * (1 - w) + right_u * w;
			double v = left_v * (1 - w) + right_v * w;
			double scale = 0.5;
			putpixel(d, x, y, getpixel2(d->texture[wall.sector.floorpicnum],
						u * scale, v * scale));
		}
	}
}
