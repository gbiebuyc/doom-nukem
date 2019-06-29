/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_anim_state.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 22:42:43 by nallani           #+#    #+#             */
/*   Updated: 2019/06/29 14:44:08 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define SPEED_ANIM 10
#define SPEED_ANIM_CHARG 7
#define SPEED_ANIM_CHOW 17
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

void	anim_id_1(t_monster *monster, t_monster_type *monster_type)
{
	monster->anim_time--;
	if (monster->anim_time)
		return ;
	monster->anim_state = monster_type[monster->
		id_type].anim_order[monster->anim_state];
	if (monster->anim_state < 4)
		monster->anim_time = SPEED_ANIM_CHARG;
	else
		monster->anim_time = SPEED_ANIM_CHOW;
}

void	monster_anim_state(t_monster *monster,
		t_monster_type *monster_type, t_data *d)
{
	if (monster->id_type == MOTHERDEMON)
		anim_id_0(monster, monster_type, d);
	if (monster->id_type == CHARGINGDEMON)
		anim_id_1(monster, monster_type);
}
