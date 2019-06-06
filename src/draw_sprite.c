/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 02:27:33 by nallani           #+#    #+#             */
/*   Updated: 2019/06/06 20:16:27 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	display_sprite_one_point(t_data *d, SDL_Surface *s,
		t_display_data display_data)
{
	int		x;
	int		y;
	int		colo;

	x = display_data.cut_start;
	while (x <= display_data.cut_end)
	{
		y = ft_max(display_data.ytop[x], display_data.start.y);
		while (y <= ft_min(display_data.ybot[x], display_data.end.y))
		{
			colo = getpixel(s, display_data.scale.x * (x - display_data.start.x),
					display_data.scale.y * (y - display_data.start.y));
			colo = alpha(((uint32_t *)d->screen->pixels)[x + y * d->screen->w], colo);
			putpixel(d, x, y, colo);
			y++;
		}
		x++;
	}
}

t_vec3f		transform_vec3f_to_screen(t_data *d, t_vec3f v)
{
	t_vec3f	new;
	t_vec3f dist;

	dist = sub_vec3f(v, d->cam.pos);
	new = sub_vec3f(v, d->cam.pos);
	dist.z = dist.x * d->cam.sin + dist.z * d->cam.cos;
	new = (t_vec3f){
		new.x * d->cam.cos - new.z * d->cam.sin,
			new.y,
			new.x * d->cam.sin + new.z * d->cam.cos
	};
	new.x /= dist.z;
	new.y /= dist.z;
	new.x = new.x *  WIDTH + WIDTH * 0.5;
	new.y = new.y * -WIDTH + HEIGHT * 0.5 - d->cam.y_offset;
	return (new);
}

void	draw_projectile(t_data *d, t_frustum *fr,
		t_projectile proj)
{
	double			dist;
	t_display_data	a;
	t_vec3f			point_in_screen;

	point_in_screen = transform_vec3f_to_screen(d, proj.pos);

	if (point_in_screen.z <= 0)
		return ;
	dist = vec3f_length(sub_vec3f(proj.pos, d->cam.pos));
	a.start.x = point_in_screen.x - (d->projectile_tex[proj.weapon_id][proj.current_anim_playing]->w * d->projectile_type[proj.id_type].size) / dist; // a modifier 
	a.end.x = point_in_screen.x + (d->projectile_tex[proj.weapon_id][proj.current_anim_playing]->w * d->projectile_type[proj.id_type].size) / dist; //same
	a.scale.x = fabs(100.0 / (a.start.x - a.end.x) * 0.01);
	a.cut_start = ft_max(a.start.x, fr->x1);
	a.cut_end = ft_min(a.end.x, fr->x2);

	a.start.y = point_in_screen.y - (d->projectile_tex[proj.weapon_id][proj.current_anim_playing]->h * d->projectile_type[proj.id_type].size) / dist; //same
	a.end.y = point_in_screen.y + (d->projectile_tex[proj.weapon_id][proj.current_anim_playing]->h * d->projectile_type[proj.id_type].size) / dist; //same
	a.scale.y = fabs(100.0 / (a.start.y - a.end.y) * 0.01);
	a.ytop = &fr->ytop[0];
	a.ybot = &fr->ybottom[0];

	display_sprite_one_point(d, d->projectile_tex[proj.id_type][proj.current_anim_playing],
			a);
}

void	draw_monster_test(t_data *d, t_frustum *fr, t_monster monster);

void	draw_sprite(t_data *d, t_sector *sector, t_frustum *fr, t_sprite_list *sprite)
{
	(void)sector;
	if (sprite->type == IS_MONSTER)
	{
		draw_monster_test(d, fr, d->monsters[sprite->id]);
	//draw_monster(d, sector, fr, d->monsters[sprite->id]);
	}
	if (sprite->type == IS_PROJECTILE)
		draw_projectile(d, fr, d->projectiles[sprite->id]);
}
