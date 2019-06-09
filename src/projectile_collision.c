/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_collision.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 22:30:55 by nallani           #+#    #+#             */
/*   Updated: 2019/06/09 23:47:53 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		monster_hit(t_data *d, uint16_t damage, uint16_t id_monster)
{
	if ((d->monsters[id_monster].life -= damage) <= 0)
	{
		d->monsters[id_monster].can_collide = false;
		d->monsters[id_monster].activated = false;
		d->monsters[id_monster].anim_state = 10;
		d->monsters[id_monster].anim_time = 20;
	}
}
/*
void	player_hit(t_data *d, uint16_t	damage)
{
}
*/
bool		collision_proj_monster(t_data *d, t_sector *sector, t_projectile *projectile)
{
	t_vec3f			newpos;
	t_vec2f			vec2f_tmp[2];
	t_sprite_list	*tmp;
	double			dist;

	newpos = add_vec3f(projectile->pos, projectile->dir);
	tmp = sector->sprite_list;
	//add while with neighbor sectors
	while (tmp)
	{
		if (tmp->type == IS_MONSTER && d->monsters[tmp->id].can_collide)
		{
			dist = vec3f_length(sub_vec3f(newpos,
						(t_vec3f){d->monsters[tmp->id].pos.x,
						(sector->floorheight + d->monster_type[d->monsters[tmp->id].id_type].floating) + d->monster_type[d->monsters[tmp->id].id_type].height * 0.5,
						d->monsters[tmp->id].pos.y}));
			if (dist < d->projectile_type[projectile->id_type].hitbox_radius +
					d->monster_type[d->monsters[tmp->id].id_type].hitbox_radius * 
					d->monsters[tmp->id].size)
			{
				vec2f_tmp[0] = sub_vec2f((t_vec2f){projectile->pos.x,
						projectile->pos.z}, d->monsters[tmp->id].pos);
				vec2f_tmp[1] = (t_vec2f){d->monster_type[d->monsters[tmp->id].id_type].hitbox_radius
					+ d->projectile_type[projectile->id_type].hitbox_radius,
					0.0};
				actualize_dir(atan2(vec2f_tmp[0].y, vec2f_tmp[0].x), &vec2f_tmp[1]);
				projectile->pos.x = d->monsters[tmp->id].pos.x + vec2f_tmp[1].x;
				projectile->pos.z = d->monsters[tmp->id].pos.y +  vec2f_tmp[1].y;
				projectile->pos.y = (newpos.y + projectile->pos.y) * 0.5;
				monster_hit(d, d->projectile_type[projectile->id_type].damage, tmp->id);
				return (true);
			}
		}
		tmp = tmp->next;
	}
	projectile->pos = newpos;
	return (false);
}

# define MIN_DIST_TO_PLAYER 0.15

bool		collision_proj_player(t_data *d, t_projectile *projectile)
{
	t_vec3f	newpos;
	t_vec3f	tmp_pos;
	t_vec2f	tmp;
	double	dist;

	newpos = add_vec3f(projectile->pos, projectile->dir);
	dist = vec3f_length(sub_vec3f(newpos, d->cam.pos));
	if (dist < d->projectile_type[projectile->id_type].hitbox_radius + PLAYER_HITBOX)
	{
		tmp_pos = sub_vec3f(projectile->pos, d->cam.pos);
		tmp = (t_vec2f){MIN_DIST_TO_PLAYER, 0.0};
		player_hit_projectile(d, projectile);
		actualize_dir(atan2(tmp_pos.y, tmp_pos.x) - M_PI_2, &tmp);
		projectile->pos = (t_vec3f){
			tmp.x + d->cam.pos.x,
			d->cam.pos.y,
			tmp.y + d->cam.pos.z};
		projectile->pos = newpos;
		return (true);
	}
	projectile->pos = newpos;
	return (false);
}
