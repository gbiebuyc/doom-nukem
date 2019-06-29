/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_monster.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 02:27:33 by nallani           #+#    #+#             */
/*   Updated: 2019/06/29 13:23:08 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static void	display_sprite_one_point_monst(t_data *d, SDL_Surface *s,
		t_display_data display_data, double dist)
{
	int			x;
	int			y;
	uint32_t	colo;

	x = display_data.cut_start - 1;
	while (++x <= display_data.cut_end)
	{
		y = ft_max(0, display_data.start.y) - 1;
		while (++y <= ft_min(HEIGHT - 1, display_data.end.y))
		{
			if (dist < d->zbuffer[x + y * d->screen->w])
			{
				colo = getpixel(s, display_data.scale.x *
						(x - display_data.start.x),
						display_data.scale.y * (y - display_data.start.y));
				colo = alpha(((uint32_t *)d->screen->pixels)
						[x + y * d->screen->w], colo);
				if (colo != getpixel3(d->screen, x, y))
				{
					putpixel(d, x, y, colo);
					d->zbuffer[x + y * d->screen->w] = dist;
				}
			}
		}
	}
}

static void	display_sprite_one_point_rev(t_data *d, SDL_Surface *s,
		t_display_data display_data, double dist)
{
	int			x;
	int			y;
	uint32_t	colo;

	x = display_data.cut_start - 1;
	while (++x <= display_data.cut_end)
	{
		y = ft_max(0, display_data.start.y) - 1;
		while (++y <= ft_min(HEIGHT - 1, display_data.end.y))
		{
			if (dist < d->zbuffer[x + y * d->screen->w])
			{
				colo = getpixel(s, 1 - (display_data.scale.x *
							(x - display_data.start.x)),
						display_data.scale.y * (y - display_data.start.y));
				colo = alpha(((uint32_t *)d->screen->pixels)
						[x + y * d->screen->w], colo);
				if (colo != getpixel3(d->screen, x, y))
				{
					putpixel(d, x, y, colo);
					d->zbuffer[x + y * d->screen->w] = dist;
				}
			}
		}
	}
}

static void	set_display_data_proj_1(t_display_data *display_data,
		SDL_Surface *s, t_vec3f point_in_screen, double size)
{
	display_data->start.x = point_in_screen.x - (s->w) / point_in_screen.z *
		size;
	display_data->end.x = point_in_screen.x + (s->w) / point_in_screen.z *
		size;
	display_data->start.y = point_in_screen.y - (s->h * 2) / point_in_screen.z *
		size;
	display_data->end.y = point_in_screen.y;
}

static void	set_display_data_proj_2(t_display_data *display_data)
{
	display_data->scale.x = fabs(100.0 / (display_data->start.x
			- display_data->end.x) * 0.01);
	display_data->cut_start = ft_max(display_data->start.x, 0);
	display_data->cut_end = ft_min(display_data->end.x, WIDTH - 1);
	display_data->scale.y = fabs(100.0 / (display_data->start.y
				- display_data->end.y) * 0.01);
}

void		draw_monster(t_data *d, t_monster monster)
{
	t_display_data	a;
	t_vec3f			point_in_screen;
	t_vec3f			monsterpos;
	short			nb_of_anim[2];

	monsterpos = (t_vec3f){monster.pos.x, get_floorheight_point(d,
			monster.cursectnum, monster.pos), monster.pos.y};
	point_in_screen = transform_vec3f_to_screen(d, monsterpos);
	if (point_in_screen.z <= 0)
		return ;
	nb_of_anim[1] = get_nb_anim_from_rot(monster.rot,
			monster.pos, vec3to2(d->cam.pos));
	nb_of_anim[0] = nb_of_anim[1];
	if (nb_of_anim[1] > 4)
		nb_of_anim[0] = 8 - nb_of_anim[0];
	set_display_data_proj_1(&a, d->monster_text[monster.id_type][monster.
			anim_state][nb_of_anim[0]], point_in_screen,
			d->monster_type[monster.id_type].size);
	set_display_data_proj_2(&a);
	if (nb_of_anim[1] < 4 && monster.anim_state < 10)
		display_sprite_one_point_rev(d, d->monster_text[monster.id_type]
				[monster.anim_state][nb_of_anim[0]], a, point_in_screen.z);
	else
		display_sprite_one_point_monst(d, d->monster_text[monster.id_type]
				[monster.anim_state][nb_of_anim[0]], a, point_in_screen.z);
}
