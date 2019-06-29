/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_collision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 16:54:54 by nallani           #+#    #+#             */
/*   Updated: 2019/06/29 14:47:41 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define MONSTER_MIN_DIST_HITBOX 0.15
#define MINIMUM_SIZE_AROUND_MONSTERS 0.8

t_vec3f	update_pos_vec3f(t_vec3f new_pos, t_vec2f point, double radius)
{
	t_vec2f		tmp[2];
	double		angle;

	(void)new_pos;
	(void)point;
	(void)radius;
	tmp[0].x = new_pos.x - point.x;
	tmp[0].y = new_pos.z - point.y;
	tmp[1].x = radius;
	tmp[1].y = 0.0;
	angle = atan2(tmp[0].y, tmp[0].x);
	actualize_dir(angle, &tmp[1]);
	new_pos.x = tmp[1].x + point.x;
	new_pos.z = tmp[1].y + point.y;
	return (new_pos);
}

t_vec2f	update_pos_vec2f(t_vec2f pos, t_vec2f point,
		double radius)
{
	t_vec2f		tmp;
	double		angle;

	tmp = sub_vec2f(pos, point);
	angle = atan2(tmp.y, tmp.x);
	tmp.y = 0.0;
	tmp.x = MINIMUM_SIZE_AROUND_MONSTERS;
	actualize_dir(angle, &tmp);
	return (add_vec2f(point, tmp));
}

void	collision_monster_monster(t_data *d, short cur_sect, t_monster *monster)
{
	t_sprite_list	*tmp;

	tmp = d->sectors[cur_sect].sprite_list;
	while (tmp)
	{
		if (tmp->type == IS_MONSTER && d->monsters[tmp->id].can_collide &&
				&d->monsters[tmp->id] != monster)
			if (vec2f_length(sub_vec2f(d->monsters[tmp->id].pos, monster->pos))
					< MINIMUM_SIZE_AROUND_MONSTERS)
				monster->pos = update_pos_vec2f(monster->pos,
						d->monsters[tmp->id].pos, MINIMUM_SIZE_AROUND_MONSTERS);
		tmp = tmp->next;
	}
}

void	collision_with_monster(t_data *d, short cur_sect)
{
	t_sprite_list	*tmp;

	tmp = d->sectors[cur_sect].sprite_list;
	while (tmp)
	{
		if (tmp->type == IS_MONSTER && d->monsters[tmp->id].can_collide)
		{
			if (vec2f_length(sub_vec2f(d->monsters[tmp->id].pos,
							(t_vec2f){d->cam.pos.x, d->cam.pos.z})) <
					d->monster_type[d->monsters[tmp->id].id_type].hitbox_radius
					+ MONSTER_MIN_DIST_HITBOX && d->cam.pos.y <
					get_floorheight_point(d, cur_sect, d->monsters[tmp->id].pos)
					+ d->monster_type[d->monsters[tmp->id].id_type].height)
			{
				d->cam.pos = update_pos_vec3f(d->cam.pos, d->monsters
						[tmp->id].pos, d->monster_type[d->monsters[tmp->id].
						id_type].hitbox_radius + MONSTER_MIN_DIST_HITBOX);
				player_contact_monster(d, &(d->monsters[tmp->id]));
			}
		}
		tmp = tmp->next;
	}
}
