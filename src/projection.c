/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:02:41 by nallani           #+#    #+#             */
/*   Updated: 2019/04/05 18:26:16 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_vec3f		get_projected_vertex(t_data *d, t_vec3f v)
{
	t_vec3f	new;

	new = sub_vec3f(v, d->cam.pos);
	new = (t_vec3f){
		new.x * d->cam.cos_y - new.z * d->cam.sin_y,
		new.y,
		new.x * d->cam.sin_y + new.z * d->cam.cos_y
	};
	new = (t_vec3f){
		new.x,
		new.y * d->cam.cos_x - new.z * d->cam.sin_x,
		new.y * d->cam.sin_x + new.z * d->cam.cos_x,
	};
	new.x /= new.z;
	new.y /= new.z;
	new.x = new.x * FOV *  WIN_WIDTH + WIN_WIDTH / 2;
	new.y = new.y * FOV * -WIN_WIDTH + WIN_LENGTH / 2;
	return (new);
}

/*
short		get_y_start(t_vec2f start, t_vec2f end, short count)
{
	double	step;
	double	delta;

	step = start.x - end.x;
	delta = start.y - end.y;
	//printf("step: %f, delta :%f\n", step, delta);
	return ((short)(delta / step * (count)) + start.y);
}
short		get_y_end(t_vec2f start, t_vec2f end, short count)
{

}
void		draw_texture_2(t_data *d, t_texture2d text, SDL_Surface surface)
{
	short		x;
	short		y;
	double		length;
	short		end_y;
	t_vec2f		delta;
	short		start_y;

	length = text.vertex[1].x - text.vertex[0].x;
	x = text.vertex[0].x;
//	printf("length: %f\n", length);
		while (x <= text.vertex[1].x)
		{
			delta.x = (x - text.vertex[0].x) / length;
			start_y = get_y_start(text.vertex[0], text.vertex[1], (short)(x - text.vertex[0].x));
			end_y = get_y_start(text.vertex[3], text.vertex[2], (short)length);
//			printf("start_y :%d , end_y :%d\n", start_y, end_y);
			y = start_y;
			while (y <= end_y)
			{
				delta.y = fabs(((double)y - start_y) / (end_y - start_y));
//				printf("x : %d, y %d\nsurface_x :%d, surface_y :%d\n", x, y, (int)delta.x, (int)delta.y);
				putpixel(d, x, y, (uint32_t)((uint32_t *)surface.pixels)[(int)(delta.x * surface.w) + (int)(
						delta.y * surface.h * surface.w)]);
//				w_surface[x + y * WIN_WIDTH] = ((uint32_t *)surface.pixels)[(int)(delta.x * surface.w)
//					+ (int)(delta.y * surface.h * surface.w)];
				y++;
			}
			x++;
		}
}

void		draw_texture(t_data *d, t_texture3d text_3d, SDL_Surface surface)
{
	short			i;
	t_texture2d		text_2d;

	i = 0;
	while (i < 4)
	{
		text_2d.vertex[i] = projection(text_3d.vertex[i], d->camera.dir, d->camera.pos);
		i++;
	}
	i = 0;
//	while (i < 4)
//	{
//		printf("vertex[%d].x : %f, vertex[%d].y: %f\n", i, text_2d.vertex[i].x, i, text_2d.vertex[i].y);
//		i++;
//	}
	draw_texture_2(d, text_2d, surface);
}
*/
