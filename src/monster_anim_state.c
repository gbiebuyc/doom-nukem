/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_anim_state.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 22:42:43 by nallani           #+#    #+#             */
/*   Updated: 2019/06/26 00:19:03 by gbiebuyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define SPEED_ANIM 10
#define MOTHER_DEMON_ATTACK 6

void	anim_id_0(t_monster *monster, t_monster_type *monster_type, t_data *d)
{
	monster->anim_time--;
	if (monster->anim_time)
		return ;
	monster->anim_state = monster_type[monster->
		id_type].anim_order[monster->anim_state];
	monster->anim_time = SPEED_ANIM;
	if (monster->anim_state == MOTHER_DEMON_ATTACK &&
			monster->anim_time == SPEED_ANIM)
		create_projectile_monster(d, FIREBALL_1, monster);
}

void	monster_anim_state(t_monster *monster,
		t_monster_type *monster_type, t_data *d)
{
	if (monster->id_type == 0)
	{
		anim_id_0(monster, monster_type, d);
	}
}

void	destroy_mail(short id, t_sector *sector, uint8_t type_to_destroy)
{
	t_sprite_list	*tmp;
	t_sprite_list	*tmp_prev;

	tmp = sector->sprite_list;
	if (!(tmp))
		return ;
	if (tmp->id == id && tmp->type == type_to_destroy)
	{
		sector->sprite_list = tmp->next;
		free(tmp);
		return ;
	}
	tmp_prev = tmp;
	while (tmp)
	{
		if (tmp->id == id && tmp->type == type_to_destroy)
		{
			tmp_prev->next = tmp->next;
			free(tmp);
			return ;
		}
		tmp_prev = tmp;
		tmp = tmp->next;
	}
}

void	update_anim_projectile(t_projectile *projectile, t_data *d, short id,
		bool has_collided)
{
	if (has_collided)
	{
		projectile->dir = (t_vec3f){0.0, 0.0, 0.0};
		projectile->has_collided = true;
		projectile->current_anim_playing =
			d->projectile_type[projectile->id_type].anim_order[COLLISION_ID];
		projectile->time_remaining_anim = 5;
		return ;
	}
	if (projectile->time_remaining_anim)
	{
		projectile->time_remaining_anim--;
		return ;
	}
	if (d->projectile_type[projectile->id_type].anim_order[
			projectile->current_anim_playing] == MUST_BE_DESTROYED)
	{
		projectile->is_active = false;
		destroy_mail(id, &d->sectors[projectile->cursectnum], IS_PROJECTILE);
		return ;
	}
	projectile->current_anim_playing = d->projectile_type[projectile->
		id_type].anim_order[projectile->current_anim_playing];
	projectile->time_remaining_anim = 2;
}
