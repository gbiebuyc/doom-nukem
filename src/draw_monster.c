/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_monster.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 02:27:33 by nallani           #+#    #+#             */
/*   Updated: 2019/06/28 18:26:08 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

uint8_t	get_nb_anim_from_rot_2(double rot)
{
	if (rot > 0.75 * M_PI)
		return (2);
	if (rot > M_PI_2)
		return (3);
	if (rot > M_PI_4)
		return (4);
	if (rot < 0)
		return (6);
	return (5);
}

uint8_t	get_nb_anim_from_rot(double monster_rot,
		t_vec2f monster_pos, t_vec2f player_pos)
{
	double	rot;
	double	vision_rot;
	t_vec2f	vision;

	vision = sub_vec2f(monster_pos, player_pos);
	vision_rot = atan2(vision.y, vision.x);
	rot = vision_rot - monster_rot;
	rot += M_PI_2;
	if (rot > 2 * M_PI)
		rot -= 2 * M_PI;
	if (rot < 0)
		rot += 2 * M_PI;
	rot = rot - 0.125 * M_PI;
	if (rot > M_PI)
	{
		if (rot < 1.25 * M_PI)
			return (1);
		if (rot < 1.5 * M_PI)
			return (0);
		if (rot < 1.75 * M_PI)
			return (7);
		if (rot < 2 * M_PI)
			return (6);
	}
	return (get_nb_anim_from_rot_2(rot));
}

void	display_sprite_one_point_monst(t_data *d, SDL_Surface *s,
		t_display_data display_data, double dist)
{
	int		x;
	int		y;
	uint32_t		colo;

	x = display_data.cut_start;
	while (x <= display_data.cut_end)
	{
		y = ft_max(display_data.ytop[x], display_data.start.y);
		while (y <= ft_min(display_data.ybot[x], display_data.end.y))
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
			y++;
		}
		x++;
	}
}

void	display_sprite_one_point_rev(t_data *d, SDL_Surface *s,
		t_display_data display_data, double dist)
{
	int		x;
	int		y;
	uint32_t		colo;

	x = display_data.cut_start;
	while (x <= display_data.cut_end)
	{
		y = ft_max(display_data.ytop[x], display_data.start.y);
		while (y <= ft_min(display_data.ybot[x], display_data.end.y))
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
			y++;
		}
		x++;
	}
}

void	draw_monster(t_data *d, t_frustum *fr, t_monster monster)
{
	//double			dist;
	t_display_data	a;
	t_vec3f			point_in_screen;
	t_vec3f			monsterpos;
	short			nb_of_anim[2];

	monsterpos = (t_vec3f){monster.pos.x,
		get_floorheight_point(d, monster.cursectnum, monster.pos),
		monster.pos.y};
	point_in_screen = transform_vec3f_to_screen(d, monsterpos);
	if (point_in_screen.z <= 0)
		return ;
	nb_of_anim[1] = get_nb_anim_from_rot(monster.rot,
			monster.pos, vec3to2(d->cam.pos));
	nb_of_anim[0] = nb_of_anim[1];
	if (nb_of_anim[1] > 4)
		nb_of_anim[0] = 8 - nb_of_anim[0];
	//	dist = vec3f_length(sub_vec3f((t_vec3f){monsterpos.x,
	//				monsterpos.y + monster.height / 2,
	//				monsterpos.z}
	//				, d->cam.pos));
	a.start.x = point_in_screen.x - (d->monster_text[monster.id_type]
			[monster.anim_state][nb_of_anim[0]]->w) / point_in_screen.z *
		d->monster_type[monster.id_type].size;
	a.end.x = point_in_screen.x + (d->monster_text[monster.id_type]
			[monster.anim_state][nb_of_anim[0]]->w) / point_in_screen.z *
		d->monster_type[monster.id_type].size;
	a.scale.x = fabs(100.0 / (a.start.x - a.end.x) * 0.01);
	a.cut_start = ft_max(a.start.x, fr->x1);
	a.cut_end = ft_min(a.end.x, fr->x2);
	a.start.y = point_in_screen.y - (d->monster_text[monster.id_type]
			[monster.anim_state][nb_of_anim[0]]->h * 2) /
		point_in_screen.z * d->monster_type[monster.id_type].size;
	a.end.y = point_in_screen.y;
	a.scale.y = fabs(100.0 / (a.start.y - a.end.y) * 0.01);
	a.ytop = &fr->ytop[0];
	a.ybot = &fr->ybottom[0];
	if (nb_of_anim[1] < 4 && monster.anim_state < 10)
		display_sprite_one_point_rev(d, d->monster_text[monster.id_type]
				[monster.anim_state][nb_of_anim[0]], a, point_in_screen.z);
	else
		display_sprite_one_point_monst(d, d->monster_text[monster.id_type]
				[monster.anim_state][nb_of_anim[0]], a, point_in_screen.z);
}
