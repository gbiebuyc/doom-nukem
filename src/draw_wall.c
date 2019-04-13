/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:38:27 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/04/13 15:26:42 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	draw_wall(t_data *d, t_vec3f left, t_vec3f right, uint32_t color)
{
	t_vec3f left2 = left;
	left.y += d->sectors[0].ceilheight;
	left2.y += d->sectors[0].floorheight;
	t_vec3f right2 = right;
	right.y += d->sectors[0].ceilheight;
	right2.y += d->sectors[0].floorheight;

	apply_perspective(d, &left);
	apply_perspective(d, &right);
	apply_perspective(d, &left2);
	apply_perspective(d, &right2);

	double y_start = left.y;
	double y_end = left2.y;
	int stepx = right.x - left.x;
	double dy_start = (right.y - left.y) / stepx;
	double dy_end = (right2.y - left2.y) / stepx;
	for (int x = left.x; x <= right.x; x++)
	{
		for (int y = y_start; y <= y_end; y++)
			putpixel(d, x, y, color);
		y_start += dy_start;
		y_end += dy_end;
	}
}
