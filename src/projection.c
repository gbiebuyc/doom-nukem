/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:02:41 by nallani           #+#    #+#             */
/*   Updated: 2019/04/03 19:42:27 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_vec2f		projection(t_vec3f vec3, t_vec3f dir, t_vec3f pos)
{
	t_vec2f	result;
	double	angle;

	vec3 = sub_vec3f(vec3, pos);
	angle = get_vec2f_angle((t_vec2f){dir.x, dir.z}, (t_vec2f){0, 1});
	result.x = cos(angle) * vec3.x - sin(angle) * vec3.z;
	result.y = vec3.y;
	vec3.z = sin(angle) * vec3.x + cos(angle) * vec3.z;
	result.x /= vec3.z;
	result.y /= vec3.z;	
	result.x = result.x * WIN_WIDTH + WIN_WIDTH / 2;
	result.y = result.y * -WIN_WIDTH + WIN_LENGTH / 2;
	return (result);
}

double		get_y_start(t_vec2f start, t_vec2f end, short count)
{
	double	step;
	double	delta;

	step = (double)start.x - (double)end.x;
	delta = (double)start.y - (double)end.y;
	//printf("step: %f, delta :%f\n", step, delta);
	return ((delta / step * (count)) + start.y);
}
/*
short		get_y_end(t_vec2f start, t_vec2f end, short count)
{

}
*/
void		draw_texture_2(t_data *d, t_texture2d text, SDL_Surface surface) //probleme avec la composante verticale de pos (delta.y ?)
{
	short		x;
	short		y;
	double		length;
	double		end_y;
	t_vec2f		delta;
	double		start_y;

	length = text.vertex[1].x - text.vertex[0].x;
	x = text.vertex[0].x;
//	printf("length: %f\n", length);
		while (x <= text.vertex[1].x)
		{
			delta.x = (x - (short)text.vertex[0].x) / length;
			start_y = get_y_start(text.vertex[0], text.vertex[1], (short)(x - text.vertex[0].x));
			end_y = get_y_start(text.vertex[3], text.vertex[2], (short)(x - text.vertex[0].x));
// 			printf("start_y :%d , end_y :%d\n", start_y, end_y);
			y = (short)start_y;
			while (y <= (short)end_y)
			{
				delta.y = fabs((double)((double)y - start_y) / (end_y - start_y));
				//printf("x : %d, y %d\nsurface_x :%f, surface_y :%f\n", x, y, delta.x, delta.y);
				uint32_t pos = (int)(delta.x * surface.w) + (int)(delta.y * surface.h * (surface.w));
				putpixel(d, x, y, (uint32_t)((uint32_t*)surface.pixels)[pos]);
		//		uint32_t	colo;
		//		colo = SDL_MapRGB(NULL, (uint8_t)((char*)surface.pixels)[pos], (uint8_t)((char*)surface.pixels)[pos + 1],
		//				(uint8_t)((char*)surface.pixels)[pos + 2]);
		//		putpixel(d, x, y, colo);
	//			printf("x :%d\n", (int)(delta.x * surface.w));
	//			printf("y :%d\n", (int)(delta.y * surface.h * surface.w));
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
