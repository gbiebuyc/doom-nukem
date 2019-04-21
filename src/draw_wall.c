/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:38:27 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/04/21 04:14:57 by gbiebuyc         ###   ########.fr       */
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
			x <= ft_min(WIN_WIDTH, wall.right.x);
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
