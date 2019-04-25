/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:38:27 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/04/26 17:39:09 by gbiebuyc         ###   ########.fr       */
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
		double n = norm(x, wall.left.x, wall.right.x);
		n = fclamp(n, 0, 1);
		double z = 1 / lerp(n, wall.left.z, wall.right.z);
		double u = lerp(n, wall.left_u, wall.right_u) * z;

		double y_start = lerp(n, wall.left.y, wall.right.y);
		double y_end = lerp(n, wall.left2.y, wall.right2.y);
		for (int y = ft_max(0, y_start); y <= ft_min(HEIGHT - 1, y_end); y++)
		{
			double v = lerp(norm(y, y_start, y_end), 0, wall.y_scale);
			putpixel(d, x, y, getpixel2(d->texture[wall.middlepicnum], u, v));
		}
	}
}

void	draw_floor(t_data *d, t_wall_clipped wall)
{
	double n;

	int y_start = ft_min(wall.left2.y, wall.right2.y);
	int slope_end = ft_max(wall.left2.y, wall.right2.y);
	int x1 = (wall.left2.y < wall.right2.y) ? wall.left2.x : wall.right2.x;
	double altitude = d->cam.pos.y - wall.sector.floorheight;
	if (altitude <= 0)
		return ;
	altitude *= 2.7;
	double angle = -d->cam.rot + M_PI_2;
	for (int y = ft_max(0, y_start); y < HEIGHT; y++)
	{
		n = norm(y - HEIGHT / 2 + d->cam.y_offset, 0, HEIGHT / 2);
		double distance = altitude / n;
		double line_du = sin(angle) * distance;
		double line_dv = -cos(angle) * distance;
		double left_u = d->cam.pos.x + distance * cos(angle) - line_du / 2;
		double right_u = left_u + line_du;
		double left_v = d->cam.pos.z + distance * sin(angle) - line_dv / 2;
		double right_v = left_v + line_dv;

		n = fclamp(norm(y, y_start, slope_end), 0, 1);
		int x_start = lerp(n, x1, wall.left2.x);
		int x_end = lerp(n, x1, wall.right2.x);
		for (int x = ft_max(0, x_start); x <= ft_min(WIDTH, x_end); x++)
		{
			n = norm(x, 0, WIDTH);
			double u = lerp(n, left_u, right_u);
			double v = lerp(n, left_v, right_v);
			double scale = 1;
			putpixel(d, x, y, getpixel2(d->texture[wall.sector.floorpicnum],
						u * scale, v * scale));
		}
	}
}
