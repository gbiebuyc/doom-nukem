/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kits <unkown@noaddress.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 08:46:52 by Kits              #+#    #+#             */
/*   Updated: 2019/06/07 01:24:37 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

# define SIZE_OF_WEAP 1.5;
# define MAX_INERTIA 0.19//must change MOVE_SPEED in movement.c to scale properly // change along define in inertia.c

void	display_weapon(t_data *d, SDL_Surface *s, t_vec2f start, t_vec2f end)
{
	t_vec2f			scale;
	short			x;
	short			y;
	uint32_t		colo;

	scale.x = 100.0 / (end.x - start.x) * 0.01;
	scale.y = 100.0 / (end.y - start.y) * 0.01;
	x = start.x;
	while (x < end.x)
	{
		y = start.y;
		while (y < ft_min(HEIGHT, end.y))
		{
			colo = getpixel(s, scale.x * (x - start.x), scale.y * (y - start.y));
			colo = alpha(((uint32_t *)d->screen->pixels)[x + y * d->screen->w], colo);
			putpixel(d, x, y, colo);
			y++;
		}
		x++;
	}
}

void	draw_weapon(t_data *d)
{
	t_vec2f			start;
	t_vec2f			end;
	t_vec2f			tmp;
	SDL_Surface		*cur_img;

	if (!d->player.timer_anim_weap)
	{
		d->player.current_anim_playing = d->player.weapon_anim
		[d->player.current_weapon][d->player.current_anim_playing];
		d->player.timer_anim_weap = d->player.speed_anim[d->player.current_weapon];
	}
	cur_img = d->weapon_tex[d->player.current_weapon][d->player.current_anim_playing];
	d->player.timer_anim_weap--;
	start.x = WIDTH * 0.5 + d->player.timer_change_weap * WIDTH * 0.003  -
	cur_img->w * 0.5 * SIZE_OF_WEAP;
	tmp = d->inertia;
	actualize_dir(d->cam.rot, &tmp);
	start.x += tmp.x * 100;	
	end.x = start.x + cur_img->w * SIZE_OF_WEAP;
	end.y = HEIGHT + d->player.timer_change_weap * HEIGHT * 0.010 + MAX_INERTIA * 50;
	end.y += tmp.y * 50;
	start.y = end.y - cur_img->h * SIZE_OF_WEAP;
	display_weapon(d, cur_img, start, end);
}
