/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_anim_state.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nallani <unkown@noaddress.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 22:42:43 by nallani           #+#    #+#             */
/*   Updated: 2019/05/07 23:19:58 by nallani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

# define SPEED_ANIM 10 // smaller = faster

void	anim_id_0(t_monster *monster, t_monster_type *monster_type)
{
	monster->anim_time--;

	if (monster->anim_time)
		return ;
	monster->anim_state = monster_type[monster->id_type].anim_order[monster->anim_state];
	monster->anim_time = SPEED_ANIM;
}

void	monster_anim_state(t_monster *monster, t_monster_type *monster_type)
{
	if (monster->id_type == 0)
	{
		anim_id_0(monster, monster_type);
	}
}
