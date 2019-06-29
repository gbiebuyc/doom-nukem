/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 02:27:33 by nallani           #+#    #+#             */
/*   Updated: 2019/06/29 13:20:25 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		display_sprite_one_point_proj(t_data *d, SDL_Surface *s,
		t_display_data display_data, double dist)
{
	int			x;
	int			y;
	uint32_t	colo;

	x = display_data.cut_start;
	while (x <= display_data.cut_end)
	{
		y = ft_max(display_data.ytop[x], display_data.start.y);
		while (y <= ft_min(display_data.ybot[x], display_data.end.y))
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
			y++;
		}
		x++;
	}
}

t_vec3f		transform_vec3f_to_screen(t_data *d, t_vec3f v)
{
	t_vec3f	new;

	new = sub_vec3f(v, d->cam.pos);
	new = (t_vec3f){
		new.x * d->cam.cos - new.z * d->cam.sin,
			new.y,
			new.x * d->cam.sin + new.z * d->cam.cos
	};
	new.x /= new.z;
	new.y /= new.z;
	new.x = new.x * WIDTH + WIDTH * 0.5;
	new.y = new.y * -WIDTH + HEIGHT * 0.5 - d->cam.y_offset;
	return (new);
}

static void	set_display_data_proj(t_frustum *fr, t_display_data *display_data)
{
	display_data->scale.x = fabs(100.0 / (display_data->start.x
				- display_data->end.x) * 0.01);
	display_data->cut_start = ft_max(display_data->start.x, fr->x1);
	display_data->cut_end = ft_min(display_data->end.x, fr->x2);
	display_data->scale.y = fabs(100.0 / (display_data->start.y
				- display_data->end.y) * 0.01);
	display_data->ytop = &fr->ytop[0];
	display_data->ybot = &fr->ybottom[0];
}

void		draw_projectile(t_data *d, t_frustum *fr,
		t_projectile proj)
{
	double			dist;
	t_display_data	a;
	t_vec3f			point_in_screen;

	point_in_screen = transform_vec3f_to_screen(d, proj.pos);
	if (point_in_screen.z <= 0)
		return ;
	dist = vec3f_length(sub_vec3f(proj.pos, d->cam.pos));
	a.start.x = point_in_screen.x - (d->projectile_tex[proj.weapon_id]
			[proj.current_anim_playing]->w *
			d->projectile_type[proj.id_type].size) / dist;
	a.end.x = point_in_screen.x + (d->projectile_tex[proj.weapon_id]
			[proj.current_anim_playing]->w *
			d->projectile_type[proj.id_type].size) / dist;
	a.start.y = point_in_screen.y - (d->projectile_tex[proj.weapon_id]
			[proj.current_anim_playing]->h *
			d->projectile_type[proj.id_type].size) / dist;
	a.end.y = point_in_screen.y + (d->projectile_tex[proj.weapon_id]
			[proj.current_anim_playing]->h *
			d->projectile_type[proj.id_type].size) / dist;
	set_display_data_proj(fr, &a);
	display_sprite_one_point_proj(d, d->projectile_tex[proj.id_type]
			[proj.current_anim_playing], a, point_in_screen.z);
}

void		draw_sprite(t_data *d, t_frustum *fr, t_sprite_list *sprite)
{
	if (sprite->type == IS_MONSTER)
		draw_monster(d, d->monsters[sprite->id]);
	if (sprite->type == IS_PROJECTILE)
		draw_projectile(d, fr, d->projectiles[sprite->id]);
}
