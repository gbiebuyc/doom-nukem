/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blaster_col.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 17:50:43 by nallani           #+#    #+#             */
/*   Updated: 2019/07/03 17:36:46 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define BLASTER_HITBOX 0.4
#define LEFT_MOUSE_BLASTER_DAMAGE 35
#define RIGHT_MOUSE_BLASTER_DAMAGE 35

bool		should_touch_blaster_hitbox(t_data *d, t_vec2f updated_pos,
		double dist, uint16_t id_of_monst)
{
	if (updated_pos.y > 0 && updated_pos.x > -BLASTER_HITBOX -
			d->monster_type[d->monsters[id_of_monst].id_type].hitbox_radius &&
			updated_pos.x < BLASTER_HITBOX +
			d->monster_type[d->monsters[id_of_monst].id_type].hitbox_radius)
		if (d->monsters[id_of_monst].can_collide && (dist == -1 ||
					get_vec2f_length(sub_vec2f(vec3to2(d->cam.pos),
							d->monsters[id_of_monst].pos)) < dist))
			return (true);
	return (false);
}

int16_t		scan_sect_point_line(t_data *d, uint16_t sect_to_scan, double dist,
		bool hit_all)
{
	t_sprite_list	*tmp;
	t_vec2f			pos;
	int16_t			id;

	tmp = d->sectors[sect_to_scan].sprite_list;
	id = -1;
	while (tmp)
	{
		if (tmp->type == IS_MONSTER)
		{
			pos = d->monsters[tmp->id].pos;
			pos.x -= d->cam.pos.x;
			pos.y -= d->cam.pos.z;
			actualize_dir(d->cam.rot, &pos);
			if (should_touch_blaster_hitbox(d, pos, dist, tmp->id))
			{
				if (hit_all)
					monster_hit(d, RIGHT_MOUSE_BLASTER_DAMAGE, tmp->id);
				else
					id = tmp->id;
			}
		}
		tmp = tmp->next;
	}
	return (id);
}

double		get_dist_to_intersect_wall(t_data *d, t_vec2f wall1, t_vec2f wall2)
{
	double	dist;
	t_vec2f	intersec;
	t_vec2f	pos2;

	pos2 = (t_vec2f){d->cam.pos.x + 100000 * d->cam.sin,
		d->cam.pos.z + 100000 * d->cam.cos};
	dist = -1;
	intersec = intersect(vec3to2(d->cam.pos), pos2, wall1, wall2);
	if (is_inside_vec2f(wall1, wall2, intersec) &&
			is_inside_vec2f(vec3to2(d->cam.pos), pos2, intersec))
		dist = get_vec2f_length(sub_vec2f(vec3to2(d->cam.pos), intersec));
	return (dist);
}

void		blaster_shot(t_data *d)
{
	int16_t		id_of_monst;

	if (d->player.click == RIGHT_CLICK)
	{
		recur_scan_point_line(d, d->cursectnum, -1, true);
		change_buf_colo(d, 10, GREEN_BLAST);
		d->weapon_type[BLASTER].current_ammo -= 2;
	}
	if (d->player.click == LEFT_CLICK)
	{
		id_of_monst = recur_scan_point_line(d, d->cursectnum, -1, false);
		if (id_of_monst != -1)
			monster_hit(d, LEFT_MOUSE_BLASTER_DAMAGE, id_of_monst);
		change_buf_colo(d, 5, GREEN_BLAST);
		d->weapon_type[BLASTER].current_ammo -= 1;
	}
}
