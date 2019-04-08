/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbiebuyc <gbiebuyc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:38:27 by gbiebuyc          #+#    #+#             */
/*   Updated: 2019/04/08 05:17:52 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	draw_wall(t_data *d, t_wall wall, t_wall projected)
{
	/*
	if (projected.a.x >= projected.b.x)
		return ;
	*/
	(void)projected;
	SDL_Surface *tex = d->texture[0];
	t_vec3f dx_world = mul_vec3f(sub_vec3f(wall.b, wall.a), 1.0 / tex->w);
	t_vec3f dy_world = mul_vec3f(sub_vec3f(wall.d, wall.a), 1.0 / tex->h);
	t_vec3f y_world = wall.a;
	t_vec3f x_world;
	for (int y = 0; y < tex->h; y++)
	{
		x_world = y_world;
		for (int x = 0; x < tex->w; x++)
		{
			t_vec3f px = get_projected_vertex(d, x_world);
			putpixel(d, px.x, px.y, getpixel(tex, x, y));
			x_world = add_vec3f(x_world, dx_world);
		}
		y_world = add_vec3f(y_world, dy_world);
	}

}
