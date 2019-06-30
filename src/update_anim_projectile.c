/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_anim_projectile.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kits <unkown@noaddress.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 21:07:06 by Kits              #+#    #+#             */
/*   Updated: 2019/06/30 16:43:54 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define NB_OF_SECTOR_DEPTH 2

void	update_collided_proj(t_data *d, t_projectile *projectile, bool anim,
		short id)
{
	int16_t		update_sec;

	if (anim)
		projectile->time_remaining_anim--;
	if (!anim)
	{
		projectile->current_anim_playing = d->projectile_type[projectile->
			id_type].anim_order[projectile->current_anim_playing];
		projectile->time_remaining_anim = 2;
	}
	if (projectile->target)
	{
		projectile->pos = add_vec3f(vec2to3(projectile->target->pos),
				projectile->dir);
		if ((update_sec = update_cursect_proj((int16_t[2]){projectile->
						cursectnum, -1}, d, NB_OF_SECTOR_DEPTH,
						projectile->pos)) != -1)
		{
			if (update_sec != projectile->cursectnum)
				swap_list(IS_PROJECTILE, id, d,
								(int[2]){projectile->cursectnum, update_sec});
			projectile->cursectnum = update_sec;
		}
	}
}

void	update_anim_projectile(t_projectile *projectile, t_data *d, short id,
		bool has_collided)
{
	if (has_collided)
	{
		if (d->projectile_type[projectile->id_type].threat_to_player)
			projectile->dir = (t_vec3f){0.0, 0.0, 0.0};
		projectile->has_collided = true;
		projectile->current_anim_playing =
			d->projectile_type[projectile->id_type].anim_order[COLLISION_ID];
		projectile->time_remaining_anim = 5;
		play_sound(d, EXPLOSION_SOUND, vec3to2(projectile->pos));
		return ;
	}
	if (projectile->time_remaining_anim)
	{
		update_collided_proj(d, projectile, true, id);
		return ;
	}
	if (d->projectile_type[projectile->id_type].anim_order[
			projectile->current_anim_playing] == MUST_BE_DESTROYED)
	{
		projectile->is_active = false;
		destroy_mail(id, &d->sectors[projectile->cursectnum], IS_PROJECTILE);
		return ;
	}
	update_collided_proj(d, projectile, false, id);
}
